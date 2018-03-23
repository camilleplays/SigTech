
./fft $1 $2 | awk '{print $2}' | sed '1d' | sed 's/\,//g' > values_y
python curves.py | sed 's/\\n//g' | sed 's/'\''//g'

