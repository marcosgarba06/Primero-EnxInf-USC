#Práctica 5

#consejo(con los intervalos de confianza nunca debe aparecer una letra griega)
#una muestra debe ser representativa
#con una cantidad ALEATORIA conocida estimar una fija desconocida

#ejercicio 1
#generar muestras de tamaño n (distribución normal)
n = 10
x10 = rnorm(n,mean=5,sd=1)
x10				 #estas son las muestras con n=10  //
mean(x) 		 	 #media de las muestras

n = 500
x = rnorm(n,mean=5,sd=1)
x				#muestra con n=500
mean(x)

#para saber el numero que deja un 96% (1 - alpha/2)//
qt(0.96,df=9)	#9 grados de libertad	//
t=sqrt(n)*(mean(x)-5)/sd(x)    #sd es la cuasidesviación tipica   //

t
M=500
n=10
t=numeric(M) 		#para que sepa que es un vector
for (i in 1:M){		#para crear 500 muestras con tdestudent(de tamaño 10)
	x=rnorm(n,mean=5,sd=1)
	t[i]=sqrt(n)*(mean(x)-5)/sd(x)}
t

quantile(t,prob=0.96)   #quantil 96% | es el Zalphamedios

mean(x)-2.07*sd(x)/sqrt(n)		#extremo inferior del intervalo de confianza
mean(x)+2.07*sd(x)/sqrt(n)		#extremo superior

#ej 2
x=c(12.5,13.2,11.8,12.9,13.5,12.2,11.9,12.7,13.1,12.4)

mean(x)-1.97*sd(x)/sqrt(n)		
mean(x)+1.97*sd(x)/sqrt(n)

install.packages("LearningStats")  #instalar esto pa ver el intervalo con "Mean.CI(x,conf.level = 0.92)"
library(LearningStats)

#ej 3
#dos servidores (distribución normal)
#nos dan la media muestral, la varianza muestral y el tamaño de muestra de cada uno
#las muestras son independientes entre si
#el intervalo es la resta de las medias poblacionales
#la varianza de una suma es la suma de las varianzas (cuando son indep. o ns)

#ej 4. intervalos para una proporcion
#1 para éxito y 0 para el fracaso(bernoulli)
#si n es grande, p gorro se distribuye como una normal

M=500
n=100
pgorro=numeric(M) 		#para que sepa que es un vector
for (i in 1:M){
	x=rbinom(n,size=1,prob=0.7)
	pgorro[i]=mean(x)}
pgorro
x
mean(x)
hist(pgorro)
plot(density(pgorro))

qnorm(0.975)
x=rbinom(n,size=1,prob=0.7)
pgorro=mean(x)
#extremos IC:         al tener el 0.7 dentro del intervalo se acierta
pgorro-1.96*sqrt(pgorro*(1-pgorro)/n)
pgorro+1.96*sqrt(pgorro*(1-pgorro)/n)

#ej inventado
pgorro=1/9
pgorro-1.96*sqrt(pgorro*(1-pgorro)/n)
pgorro+1.96*sqrt(pgorro*(1-pgorro)/n)


#ej 7. IC de varianza poblacional (sigma al cuadrado)

n=10
M=500
chi2=numeric(M)
for (i in 1:M){
	x=rnorm(n,mean=3,sd=1/2)
	chi2[i]=(n-1)*var(x)/(0.5)^2}
chi2
plot(density(chi2))

qchisq(0.975,df=n-1)      #quartil de chi caudrado   //
qchisq(0.025,df=n-1)
#intervalo				//
x=rnorm(n,mean=3,sd=1/2)
(n-1)*var(x)/qchisq(0.975,df=n-1)
(n-1)*var(x)/qchisq(0.025,df=n-1)

#ej 8. confianza 97
n=c(2.1, 2.4, 2.0, 2.5, 2.3, 2.2, 2.6, 2.1, 2.3, 2.4, 2.2, 2.5)
n=length(x)
(n-1)*var(x)/qchisq(0.975,df=n-1)
(n-1)*var(x)/qchisq(0.025,df=n-1)



