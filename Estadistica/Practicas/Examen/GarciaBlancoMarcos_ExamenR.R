#Ejercicio 1
datos = read.table("datos_examen_lunes.txt", header = T, sep=";" , dec=".")
head(datos)
#Variable cualitativa ordinal (nivel)
ni = table(datos$nivel); ni
n = length(datos$nivel) 
fi = ni/n; fi
Ni = cumsum(ni); Ni
Fi = cumsum(fi); Fi
taboa=cbind(ni,fi,Ni,Fi);taboa
#Se puede representar con un diagrama de sectores y con un diagrama de barras
pie(ni)
barplot(fi)

#Variable cuantitativa discreta (lote)
ni2 = table(datos$lote);ni2
n2 = length(datos$lote) 
fi = ni2/n2; fi2
Ni2 = cumsum(ni2); ni2
Fi2 = cumsum(fi2); Fi2
taboa2=cbind(ni,fi,Ni,Fi);taboa2

#se puede representar con un diagrama de barras
barplot(ni2)

#Ejercicio 2
#Posicion media y mediana
media = mean(datos$recursos);media
mediana = median(datos$recursos);mediana

#Dispersion cuasivarianza y desviacion típica
cuasivar=var(datos$recursos);cuasivar
des_tipica = sd(datos$recursos)*sqrt((n-1)/n); des_tipica

#Histograma
hist(datos$recursos)
#En el histograma se ve como la mayor parte de los datos se encuentran entre 0 y 300, mientras que cuanto
#mas nos alejamos del 300 va habiendo cada vez menos datos, llegando a haber alguno más allá de 800, pero
#sin que entre 700 y 800 haya alguno.

#Ejercicio 3
y = datos$ventas 
x = datos$publicidad
modelo = lm(y ~ x)
modelo
#Pendiente = 0.7556 cuando la publicidad aumenta en 1, las ventas suben un 0.7556
#Ordenada en el origen = 53.5692 Cuando no hay publicidad las ventas son de 53.5692

plot(x,y,pch=16)
abline(modelo,col=2,lwd=2)


#Coeficiente de determinacion
summary(modelo)
#determinacion(multiple R-squared): 0.7216, el modelo explica el 72.16% de
#la variabilidad de ventas respecto a la publicidad, lo que es un buen ajuste 


#Ejercicio 4
datosgrupo = datos$grupo
datosgrupo

ni = table(datosgrupo);ni

exitos = 86 #Sacado de la frecuencia absoluta de los distintos grupos
exitos

n = length(datosgrupo)

proportion.CI(x = exitos, n = n, conf.level = 0.9)
#Puntual (Proportion estimate): 0.43
#Por Intervalo de confianza: (0.37242 , 0.48758)

#Si se realiza la estimacion con un solo punto obtenemos que la proporcion de los productos del 
#grupo A es de 0.43, lo que implica que un 43% de los productos son del grupo A y el 57% son de los 
#grupos B o C
#Si se realiza en un intervalo obtenemos que dicha proporción está entre 0.37242 y 0.48758 con un 90% 
#de seguridad.

#Ejercicio 5
#X: "Media de tiempo de proguccion" (h)
#X \in N(μ, σ²)

#H0: μ0 = 5.5
#Ha: μ0 = 5.5
library(LearningStats)
Mean.test(x=datos$tiempo_produccion, mu=5.5 ,alternative = "two.sided", alpha = 0.05)
#Como T_obs esta en la region de rechazo y p-valor < alpha, rechazamos H0
#Existen evidencias estadísticamente significativas para concluir que la media de tiempos de 
#producción ha cambiado respecto al valor histórico





