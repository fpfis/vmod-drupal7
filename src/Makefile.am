AM_CPPFLAGS = @VARNISHAPI_CFLAGS@ -Wall -Werror

vmoddir = @LIBVARNISHAPI_LIBDIR@
vmod_LTLIBRARIES = libvmod_drupal7.la

libvmod_drupal7_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_drupal7_la_SOURCES = \
	vcc_if.c \
	vcc_if.h \
	vmod_drupal7.c

vcc_if.c vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_drupal7.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_drupal7.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc:
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_drupal7.vcc \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
