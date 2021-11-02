#!/bin/bash
tentativas=$1
soma_tempos=0
for tentativa in $(seq $tentativas)
do
    ./bin/sequencial matrix1.data matrix2.data
    tempo=$(tail -1 resultado_sequencial.data)
    mv "resultado_sequencial.data" $tentativa"__resultado_sequencial.data"
    soma_tempos=$((soma_tempos + tempo))
done
echo $((soma_tempos / tentativas))