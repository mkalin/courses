#!/usr/bin/perl -w

# RGB to Cyan-Magenta-Yellow-Black (CMYK) format.
# For instance, "rosy red" is 188-143-143 in RGB but
# 0-45-45-67 in CMYK
sub rgb_to_cmyk_bf {      # bf for "brute force"
    my ($r, $g, $b) = @_; # 3 arguments: red, green, blue
    my ($c, $m, $y) = (255 - $r, 255 - $g, 255 - $b);
    my $k = ($c < $m) ? ($c < $y ? $c : $y)
	              : ($m < $y ? $m : $y);
    for ($c, $m, $y) { 
	$_ -= $k; # subtract $k from each
    }
    return [$c, $m, $y, $k]; # an array reference
}
# Take a GIF image that's 1024 (height) by 768 (width) pixels
# for 1024 * 768 = 786,432 pixels in all. Each pixel has an
# RGB value. GIF images are restricted to 256 colors; hence, 
# 786,432 - 256 = 786,176 of the computations will be redundant.
# So here's a better version: one that _caches_ results.
sub rgb_to_cmyk { 
    my ($r, $g, $b) = @_;

    my $key = join ',', $r, $g, $b; # stringify the three
    # Return if already computed.
    return $cache{$key} if exists $cache{$key};

    my ($c, $m, $y) = (255 - $r, 255 - $g, 255 - $b);
    my $k = ($c < $m) ? ($c < $y ? $c : $y)
	              : ($m < $y ? $m : $y);
    for ($c, $m, $y) { 
	$_ -= $k; # subtract $k from each
    }

    # Otherwise, cache the computed value and return it.
    return $cache{$key} = [$c, $m, $y, $k]; 
}
#  Let f = the amount of time required to call rgb_to_cmyk_bf
#  Let g = the amount of time required for the cache operation
#  Let h = the "hit ratio," the probability that a value has
#          been computed already and therefore is in the cache
#
#  If g > f, there's no point in caching, as g occurs on every call.
#
#  The difference between rgb_to_cmyk_bf and rgb_to_cymk is
#
#       g - hf
#
#  That is, every time you find the goodies in the cache, you
#  save f; and h is the liklihood that you'll find the goodies.
#  At the start, h is 0 but approaches 1 with each cache addition.
#  So if g < hf, caching is worth it.


















