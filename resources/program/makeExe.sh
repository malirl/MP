for f in *.c; do 
	$1 $2 -c $f;
done;

for d in */; do
	cd $d;
	i=0;

	# for f in *.c; do
	# 	i=$(($i+1));	
	# done;

	# TO-DO: rekurzivni prochazeni
	# TO-DO: předejít kompilaci '*.c' souboru

	if [ $i -ne 1 ]
	then 
		for f in *.c; do
			$1 $2 -c $f;
		done;
	fi
	cd ..;
done;

OBJFILES="controler.o";
for f in **/*.o; do OBJFILES="${OBJFILES} $f"; done;
	$1 $2 $OBJFILES -o $3;

