for f in *.c; do 
	$1 $2 -c $f;
done;

for d in */; do
	cd $d;
	for f in *.c; do 
		$1 $2 -c $f;
	done;
	cd ..;
done;

OBJFILES="controler.o";
for f in **/*.o; do OBJFILES="${OBJFILES} $f"; done;
$1 $2 $OBJFILES -o $3;

