#! /bin/bash

func_ps()
{
	echo -e "....POWER SUPPLY....\nPOWER_SUPPLY Test Check Passed!\n"
}
func_An()
{
	echo -e "....ANTENNA....\n ANTENNA Test Check Fail!\n"
}
func_rgb()
{
	echo -e "....RGB....\nRGB Test Check Passed!\n"
}
func_mic()
{
	echo -e "....MIC....\nMIC Test Check Fail!\n"
}

echo -e "TEST CASES AVAILABLE 
		1.POWER_SUPPLY 
		2.ANTENNA
		3.RGB_LED
		4.MIC"

while true
do
	echo -e "To Select Test Case 
			Enter 1 For POWER_SUPPLY Test Check
			Enter 2 For ANTENNA Test Check
			Enter 3 For RGB_LED Test Check
			Enter 4 For MIC Test Check
			Enter 5 For Exit"
	read -p "Enter your choice :" choice

	case $choice in
		1)

			func_ps
			;;
		2)
			func_An
			;;
		3)
			func_rgb    
			;;
		4)
			func_mic
			;;  
		5)
			break      
			;;             
		*)
			echo "*****SORRY,WRONG INPUT*****"
			;;
	esac
done

