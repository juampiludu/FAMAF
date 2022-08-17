# Ejercicio 1

```console
> cat /proc/cpuinfo | grep 'model name'
model name      : Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz
```

# Ejercicio 2

```console
> cat /proc/cpuinfo | grep 'model name' | wc -l
8
```

# Ejercicio 3

```console
> wget https://www.gutenberg.org/files/11/11-0.txt && mv 11-0.txt juampa02_in_wonderland.txt && sed -i 's/Alice/juampa02/g' juampa02_in_wonderland.txt && cat juampa02_in_wonderland.txt | grep 'juampa02' && rm juampa02_in_wonderland.txt
```

# Ejercicio 4

```console
> sort -k 5n weather_cordoba.in | awk '{print $1 " " $2 " " $3}'
```

# Ejercicio 5

```console
> sort -k 3n atpplayers.in
```

# Ejercicio 6

```console
> awk '{print $1" " $2" "$3" "$4" "$5" "$6" "$7" "$8" ("$7-$8")"}' superliga.in | sort -k2,2nr -k1,9r
```

# Ejercicio 7

```console
> ip a | grep 'ether' | awk '{print $2}'
f2:9c:f6:05:d3:ef
be:09:51:cf:b4:c3
00:15:5d:05:93:dd
```

# Ejercicio 8

## a)

```console
> mkdir fma && cd fma/
> touch fma_S01E{01..10}_es.srt
```

## b)

```console
> for i in *.srt; do mv $i $(basename $i _es.srt).srt; done;
```

# Ejercicio Opcional

## a)

```console
> ffmpeg -i input.mp4 -ss 00:00:15 -c copy output1.mp4
> ffmpeg -t 00:02:16 -i output1.mp4 -c copy output2.mp4
```

## b)

```console
> ffmpeg -i input1.mp3 -i input2.mp3 -filter_complex amerge=inputs=2 output.mp3
```
En este apartado mezclo dos audios en mono y los uno en forma de estéreo.