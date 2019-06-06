#COMPILA
gcc -o borwein Borwein_paralelo.c -lm -lpthread
gcc -o calc calculos.c -lm

#VARIAVEIS
ITERACOES=30
declare -a threads=("2" "4" "8" "16")

if [ ! -d "Resultados" ];then
    mkdir Resultados
else
    rm -r Resultados #limpa para inserir novos resultados
    mkdir Resultados 
fi

for thread in "${threads[@]}"
do
    for (( i=0; i<$ITERACOES; i++ ));
    do
	    echo "Executando iteracao $i com $thread threads..."
	    ./borwein $thread 1000000000 < entrada.txt >> Resultados/$thread-saida.txt #./programa Num-THREADS E Num-ITERACOES
	    #/usr/bin/time -f "%e" ./programa < entrada.txt >> Resultados/saida.txt
    done
    mv tempo.txt $thread-tempo.txt
    mv $thread-tempo.txt Resultados
    echo "Executando Calculos $thread threads..."
    ./calc $ITERACOES Resultados/$thread-tempo.txt
done

mv Calculo.txt Resultados
echo "Execucao finalizada!"

rm borwein
rm calc
