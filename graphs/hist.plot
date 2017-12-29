#!/usr/bin/gnuplot -persist

set terminal png size 1200,900 enhanced font "Helvetica" 14

# set terminal png transparent nocrop enhanced font arial 8 size 500,350

set output 'distrplot.png'

set bar 1.000000
set boxwidth 0.9 absolute
set style fill  solid 1.00 border -1
set style rectangle back fc lt -3 fillstyle  solid 1.00 border -1
set key inside right top vertical Right noreverse enhanced autotitles columnhead nobox
set style histogram clustered gap 1 title  offset character 0, 0, 0
set datafile missing '-'
set style data histograms
set xtics border in scale 1,0.5 nomirror offset character 0, 0, 0 #rotate by -45
set title "Inter-contacts duration distribution"
set ylabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90

set cblabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
set locale "C"
plot 'distr.out' using 6:xtic(1) ti col