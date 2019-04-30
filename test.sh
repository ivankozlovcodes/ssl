#!/bin/sh

echo "pickle rick" | ./ft_ssl md5 > user_output
echo "" >> user_output

echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p >> user_output
echo "" >> user_output

echo "Pity the living." | ./ft_ssl md5 -q -r >> user_output
echo "" >> user_output

rm -rf file

echo "And above all," >> file
./ft_ssl md5 file >> user_output
./ft_ssl md5 -r file >> user_output
echo "" >> user_output

./ft_ssl md5 -s "pity those that aren't following baerista on spotify." >> user_output
echo "" >> user_output

echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file  >> user_output
echo "" >> user_output

echo "some of this will not make sense at first" | ./ft_ssl md5 file  >> user_output
echo "" >> user_output

echo "but eventually you will understand" | ./ft_ssl md5 -p -r file  >> user_output
echo "" >> user_output

echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file  >> user_output
echo "" >> user_output

echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"  >> user_output
echo "" >> user_output

echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file  >> user_output

diff test.out user_output
