import math

for i in range(1, 25):
	r = math.floor(math.log2(i))
	
	#j = i
	#counter = 0
	#while j != 1:
	#	j >>= 1
	#	counter += 1
	
	j = i
	counter = 0
	while j >>= 1:
		j >>= 1
		counter += 1

	print(f"{i:2}    {bin(i)[2:]:>5}    {r}    {counter}")
