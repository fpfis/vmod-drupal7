#include <stdlib.h>
#include <stdio.h>

#include "vrt.h"
#include "include/vsha256.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
	return 0;
}

/*
 * Given a HTTP Host and a base path, return the resulting Drupal session name.
 * Useful to compute the session cookie name of known Drupal sites.
 * This function is equivalent to suffixing SESS with the result of:
 * php -r 'echo substr(hash("sha256", "domain/base-path"), 0, 32);'
 */
const char *
vmod_session_name(struct sess *sp, const char *host, const char *base_path) {
	char *session_name;
	SHA256_CTX *sha256_ctx;
	unsigned char *digest;

	// We need 4 characters for "SESS" + the first 32 characters of the SHA256 hash + \0.
	session_name = (unsigned char *)WS_Alloc(sp->wrk->ws, 37);
	if (session_name == NULL) {
		VSL(SLT_Debug, 0, "drupal7-vmod: Unable to allocate return string to compute session name, abort");
		return NULL;
	}

	sha256_ctx = (SHA256_CTX *)WS_Alloc(sp->wrk->ws, sizeof(SHA256_CTX));
	if (sha256_ctx == NULL) {
		VSL(SLT_Debug, 0, "drupal7-vmod: Unable to allocate SHA256 context to compute session name, abort");
		return NULL;
	}

	digest = (unsigned char *)WS_Alloc(sp->wrk->ws, 32);
	if (digest == NULL) {
		VSL(SLT_Debug, 0, "drupal7-vmod: Unable to allocate SHA256 digest to compute session name, abort");
		return NULL;
	}

	// Initialize a SHA256 context.
	SHA256_Init(sha256_ctx);
	// Fill it with the host and base path.
	SHA256_Update(sha256_ctx, host, strlen(host));
	SHA256_Update(sha256_ctx, base_path, strlen(base_path));
	// Retrieve the resulting SHA256 digest...
	SHA256_Final(digest, sha256_ctx);
	// ... and express its first 128 bytes (Big Endian-wise) as 16 pairs of
	// hexadecimal digits.
	snprintf(
		session_name,
		37,
		"SESS%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
		digest[0], digest[1], digest[2], digest[3], digest[4], digest[5], digest[6], digest[7],
		digest[8], digest[9], digest[10], digest[11], digest[12], digest[13], digest[14], digest[15]
	);

	return session_name;
}
