#!/bin/bash
v=3.0.6
/home/xavier/projets/varnish-vmod/varnish-${v}/bin/varnishtest/varnishtest -Dvarnishd=/home/xavier/projets/varnish-vmod/varnish-${v}/bin/varnishd/varnishd -Dvmod_topbuild=/home/xavier/projets/varnish-vmod/libvmod-drupal7 "$@"
