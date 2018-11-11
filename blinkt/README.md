# Blinkt

## Data Frame

### Start Frame

|00000000|00000000|00000000|00000000|

Four bytes, all zeroes.

### LED Frame

One frame per LED. Most Significant Bit first.

|111|Global|BLUE|GREEN|RED|

### End Frame

|11111111|11111111|11111111|11111111|

Four bytes, all ones.
