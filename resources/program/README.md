##Build and run
```sh
cd resources/program && sudo make MP
```
 
###Syntax vstupu pro jeden objekt
```sh
./MP nazev_objektu parametr:hodnota parametr:hodnota...
```

###Dostupné objekty
- example
- cube-example
- line 
- ring
- circle
- polygon

##Argumenty objektů


##Ukázka vstupu:
```sh
./MP line B:x:900,y:900 A:y:100,x:150
```


###nekompletni zadani 
```sh
 ./MP line by:200 ax:113 bx:12 
```
###chybejici hodnota parametru 
```sh
 ./MP line ay: by:200 ax:113 bx:12
```
###"primka" 
```sh
 ./MP line ay:100 by:200 ax:113 bx:12
```
###"polygon" 
```sh
 ./MP polygon point:x:100,y:200 point:x:700,y:200 point:x:200,y:300 point:x:340,y:650 point:x:200,y:800 point:x:190,y:800 
```
###strany se protínají, polygon se nevytvoří 
```sh
 ./MP polygon point:x:100,y:200 point:x:700,y:200 point:x:200,y:300 point:x:340,y:650 point:x:200,y:800 point:x:230,y:830 
```

