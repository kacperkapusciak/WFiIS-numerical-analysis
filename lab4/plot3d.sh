# type set to 'gt'
set pm3d
unset surface
set view equal 
splot "out.dat" u 1:2:($4**2)
