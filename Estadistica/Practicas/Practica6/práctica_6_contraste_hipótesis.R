#practica 6, contraste de hipótesis
#tener en cuenta en el dosier la seccion 5 no entra (los chi cuadrado)

## ej 1: proporción, Normal triangular (0,1)
#región de rechazo -> z>c => [ ,+infinito)

qnorm(0.9)     #valor que deja 1 - alpha = 0.9
pgorro= 41/72
z=sqrt(72)*(pgorro-0.5)/0.5  #formula estatístico
z
#rechazar si z > qnorm
#conclusión: con un nivel 0.1 no existen evidencias significativas de que p>0.5

#p-valor = P(N(0,1)>1,17), siendo 1,17 = z
#p-valor
1-pnorm(z)

#cuando p-valor es más pequeño que alpha se rechaza

#con la librería (hasta sale gráfica)
n=72
exitos=41
proportion.test(x=exitos,n=n,p0=0.5,alternative = "greater",alpha=0.1)


##ej inventado, contraste bilateral, nivel s: 0.1
qnorm(0.95)  #punto crítico superior
qnorm(0.05)  #punto crítico inferior
z=sqrt(10)*(0.8-0.5)/0.5  #formula estatístico
z

#p-valor = 2*P(N(0,1)>1,89)
2*(1-pnorm(z))
#se rechaza pq es más pequeño que 0.1
#si fuera con un nivel del 0.01 entonces se aceptaría


##ej 2: contraste para la media en poblaciones normales
#librería
x=c(0.71, 0.66, 0.64, 0.49, 0.80, 0.67, 0.52, 0.81, 0.55, 0.65)
Mean.test(x=x,mu0=0.55,alternative = "greater",alpha=0.1)

#calculos
qt(0.9,df=9)   #punto crítico(1-aplha,grados de libertad)

x=c(0.71, 0.66, 0.64, 0.49, 0.80, 0.67, 0.52, 0.81, 0.55, 0.65)
n=length(x)
t=sqrt(n)*(mean(x)-0.55)/sd(x)    #estadístico t de student
t

#p-valor
1-pt(t,df=9)

#se rechaza H0, pq p-valor es más pequeño que alpha

##ej 3: varianza, chi cuadrado
#bilateral grafica -> alternative="two.sided"
tiempo=c(9.9,8.7,10.2,10.5,9.6,9.2,9.8,10.9,9.8)
variance.test(x=tiempo,sigma02=0.5,alternative = "two.sided",alpha=0.01)

#calculos
#H0: sigma^2  = 0.5
#Ha: sigma^2 != 0.5
z2=qchisq(0.995,d=8)   #punto critico
z1=qchisq(0.005,df=8)  #punto critico
z1
z2

x=tiempo
z=8*var(x)/0.5  #var de sc, cuasivarianza, varianza muestral
z

#no hai pq rechazar

##ej 4: dos poblaciones normales, independientes
#libreria
A=c(12.3, 15.4, 21.7, 17.2, 38.8, 42.1, 10.5, 23.3, 35.6, 28.4)
B=c(21.2, 18.6, 25.1, 14.7, 52.3, 65.2, 40.8, 43.4, 35.6, 42.0)
diffmean.test(x1=A,x2=B,paired=F,var.equal=T,alternative = "two.sided",
+ alpha=0.05)

##ej 5: dos poblaciones normales dependientes
##no entra a partir del ej 8


