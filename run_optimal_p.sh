
#!/bin/bash

tentativa=10

threads_medio=0
processos_medio=0

pf=$(((3200*3200)/6))
pl=$(((3200*3200)/12))
pl2=$(((3200*3200)/24))

echo -e "elementos_por_thread_processo,tempo_medio_threads,tempo_medio_processos"

mv "3200matrix1.data" "matrix1.data"
mv "3200matrix2.data" "matrix2.data"

threads_medio=$(./run_threads.sh $tentativa $pf)
processos_medio=$(./run_processos.sh $tentativa $pf)
echo -e "$pf,$threads_medio,$processos_medio"

threads_medio=$(./run_threads.sh $tentativa $pl)
processos_medio=$(./run_processos.sh $tentativa $pl)
echo -e "$pl,$threads_medio,$processos_medio"

threads_medio=$(./run_threads.sh $tentativa $pl2)
processos_medio=$(./run_processos.sh $tentativa $pl2)
echo -e "$pl2,$threads_medio,$processos_medio"

mv "matrix1.data" "3200matrix1.data"
mv "matrix2.data" "3200matrix2.data"