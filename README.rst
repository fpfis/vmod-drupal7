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

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the ``varnishtest`` tool.

Building requires the Varnish header files and uses pkg-config to find
the necessary paths.

If you have installed Varnish to a non-standard directory, you may need to
override PKG_CONFIG_PATH so configure can find varnishapi.pc.

Usage::

 ./autogen.sh
 ./configure


Make targets:

* make - builds the vmod.
* make install - installs your vmod.
* make check - runs the unit tests in ``src/tests/*.vtc``
* make distcheck - run check and prepare a tarball of the vmod.

In your VCL you could then use this vmod along the following lines::
        
        import drupal7;

        sub vcl_deliver {
                # This sets resp.http.X-Session-Name to the session name for foo.com/bar
                set resp.http.X-Session-Name = drupal7.session_name("foo.com", "/bar");
        }

COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-drupal7 project. See LICENSE for details.

* Copyright (c) 2015-2016 Xavier Guerrin
