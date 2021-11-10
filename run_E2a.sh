
#!/bin/bash

tentativa=10

threads_medio=0
processos_medio=0
i=0

p_i=$((((3200*3200)+7)/8))
p_f=$((p_i/4))

echo -e "elementos_por_thread_processo,tempo_medio_threads,tempo_medio_processos"

for ((i=p_i;i>=p_f;i=i-p_f))
do
    mv "3200matrix1.data" "matrix1.data"
    mv "3200matrix2.data" "matrix2.data"
    threads_medio=$(./run_threads.sh $tentativa $i)
    processos_medio=$(./run_processos.sh $tentativa $i)
    mv "matrix1.data" "3200matrix1.data"
    mv "matrix2.data" "3200matrix2.data"
    echo -e "$i,$threads_medio,$processos_medio"
done