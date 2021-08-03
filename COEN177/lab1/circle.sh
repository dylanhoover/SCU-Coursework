#Name: Dylan Hoover
#Date: 4/2/2021
#Title: Lab1 - circle bash script
#Discription: This code runs a bash script that makes sure the correct user is logged in then it calculates the area of a circle
#!/bin/sh

echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$

user=`whoami`

numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."

if [ $user = "dylan" ]
then
	echo "Now you can proceed!"
else
	echo "Check who logged in!"
	exit 1
fi

response="Yes"
while [ $response != "No" ]
do
	echo "Enter radius of the circle:"
	read radius
    pi=3.14159265
    area=$(echo "$pi * $radius * $radius" | bc)
    echo "The area of the circle is $area"

	echo "Would you like to repeat for another circle [Yes/No]?"
	read response
done
