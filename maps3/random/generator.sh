for i in `seq 1 $1`
do
	head -n 5 /dev/urandom > ./random-$i.map
done
