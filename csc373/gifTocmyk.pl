#!/usr/bin/perl -w

# This example comes from J. M. Dominus, Higher-Order Perl.
#
# Modern fancy printers expect images for printing in
# "Cyan-Magenta-Yello-Black" format (CMYK, with "K" as
# short for "black" because "B" is short for "blue").
# Images in other popular formats such as GIF use
# RGB values (red-green-blue). Here's the simple
# arithmetic for the conversion as a Perl subroutine:
sub rgb_to_cmyk_bf { # bf for "brute force"
    my ($r, $g, $b) = @_; # 3 arguments: red, green, blue
    my ($c, $m, $y) = (255 - $r, 255 - $g, 255 - $b);
    my $k = ($c < $m) ? ($c < $y ? $c : $y)
	              : ($m < $y ? $m : $y);
    for ($c, $m, $y) { 
	$_ -= $k; # subtract $k from each
    }
    return [$c, $m, $y, $k]; # an array
}
# Take a GIF image that's 1024 (height) by 768 (width) pixels
# for 1024 * 768 = 786,432 pixels in all. Each pixel has an
# RGB value. GIF images are restricted to 256 colors; hence, 
# 786,432 - 256 = 786,176 of the computations will be redundant.
# Here's a better version:
sub rgb_to_cmyk { 
    my ($r, $g, $b) = @_;

    my $key = join ',', $r, $g, $b; # stringify the three
    # Return if already computed.
    return $cache{$key} if exists $cache{$key}

    my ($c, $m, $y) = (255 - $r, 255 - $g, 255 - $b);
    my $k = ($c < $m) ? ($c < $y ? $c : $y)
	              : ($m < $y ? $m : $y);
    for ($c, $m, $y) { 
	$_ -= $k; # subtract $k from each
    }

    # Otherwise, cache the computed value and return it.
    return $cache{$key} = [$c, $m, $y, $k]; 
}
# A quick analysis:
#
#  Let f be the amount of time required to call rgb_to_cmyk_bf
#  Let g be the amount of time required for the cache operation
#  Let h be the "hit ratio," the probability that a value has
#  been computed already and therefore is in the cache
#
#  If g > f, there's no point in caching, as g occurs on every call
#  The difference between rgb_to_cmyk_bf and rgb_to_cymk is
#
#       k - hf
#
#  That is, every time you find the goodies in the cache, you
#  save f; and h is the liklihood that you'll find the goodies.
#  At the start, h is 0 but approaches 1 with each cache addition.
#  
#  In summary: if k < hf, the caching is worth it. 
