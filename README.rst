============
vmod_drupal7
============

-----------------------
Varnish Drupal 7 Module
-----------------------

:Author: Xavier Guerrin
:Date: 2015-02-04
:Version: 0.1
:Manual section: 3

SYNOPSIS
========

import drupal7;

DESCRIPTION
===========

Drupal 7 Varnish vmod; provides Drupal-related functions within Varnish.

FUNCTIONS
=========

session_name
------------

Prototype
        ::

                session_name(STRING host, STRING base_path)
Return value
	STRING
Description
	Return the session name Drupal 7 would compute for host and base_path.
Example
        ::

                set resp.http.X-Session-Name = drupal7.session_name("foo.com", "/bar");

INSTALLATION
============

This is an drupal7 skeleton for developing out-of-tree Varnish
vmods available from the 3.0 release. It implements the "Hello, World!" 
as a vmod callback. Not particularly useful in good hello world 
tradition,but demonstrates how to get the glue around a vmod working.

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the varnishtest tool.

Usage::

 ./configure VARNISHSRC=DIR [VMODDIR=DIR]

`VARNISHSRC` is the directory of the Varnish source tree for which to
compile your vmod. Both the `VARNISHSRC` and `VARNISHSRC/include`
will be added to the include search paths for your module.

Optionally you can also set the vmod install directory by adding
`VMODDIR=DIR` (defaults to the pkg-config discovered directory from your
Varnish installation).

Make targets:

* make - builds the vmod
* make install - installs your vmod in `VMODDIR`
* make check - runs the unit tests in ``src/tests/*.vtc``

In your VCL you could then use this vmod along the following lines::
        
        import drupal7;

        sub vcl_deliver {
                # This sets resp.http.X-Session-Name to the session name for foo.com/bar
                set resp.http.X-Session-Name = drupal7.session_name("foo.com", "/bar");
        }

HISTORY
=======

This manual page was released as part of the libvmod-drupal7 package,
demonstrating how to create an out-of-tree Varnish vmod.

For further drupal7s and inspiration check out the vmod directory:

    https://www.varnish-cache.org/vmods

COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-drupal7 project. See LICENSE for details.

* Copyright (c) 2015 Xavier Guerrin
