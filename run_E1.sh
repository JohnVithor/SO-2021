
#!/bin/bash

tentativa=10
tempo_maximo=120000
t=50

sequencial_medio=0
threads_medio=0
processos_medio=0
echo -e "tamanho_matriz,elementos_por_thread_processo,tempo_medio_sequencial,tempo_medio_threads,tempo_medio_processos"
while [ $sequencial_medio -le $tempo_maximo ]
do
    t=$((2 * t))
    ./bin/auxiliar $t $t $t $t
    p=$(((t*t)/8))
    sequencial_medio=$(./run_sequencial.sh $tentativa)
    threads_medio=$(./run_threads.sh $tentativa $p)
    processos_medio=$(./run_processos.sh $tentativa $p)
    mv "matrix1.data" $t"matrix1.data"
    mv "matrix2.data" $t"matrix2.data"
    echo -e "$t,$p,$sequencial_medio,$threads_medio,$processos_medio"
done