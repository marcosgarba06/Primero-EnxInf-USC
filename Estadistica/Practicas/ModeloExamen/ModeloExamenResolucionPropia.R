#Ejercicio 1:
#Cargar datos
datos = read.table("0_datos_modelo_examen.txt",header=T,sep=";",dec=".")
#headeres si tiene cabecera, sep es como se separan las columnas y dec es el simboolo de decimal
#Se comprueba si esta bien:
head(datos)
dim(datos)

#Variable cualitativa ordinal (nivel)
nivelDatos=factor(datos$nivel, levels=c("bajo", "medio", "alto"))

#Como es una cualitativa oridinal la tabla es completa
ni = table(nivelDatos); ni
n = length(nivelDatos); n
fi = ni/n; fi
Ni = cumsum(ni); ni
Fi = cumsum(fi); Fi
tab=cbind(ni,fi,Ni,Fi);tab

barplot(ni, col = "green", border = "black", main = "Diagrama de barras de ni", space = 2)
barplot(fi)
pie(fi) 

#Cuantitativa discreta (lote)
lotef = factor(datos$lote)
ni=table(datos$lote);ni
n = length(datos$lote)
fi= ni/n;fi
Ni = cumsum(ni);Ni
Fi = Ni/n;Fi
Fi2= cumsum(fi); Fi2
tab=cbind(ni,fi,Ni,Fi);tab
mean(datos$lote);sd(datos$lote);var(datos$lote) #Var devovia sc² y sd devuelve desviacion típica
#Para pasar de sc² a s² s²=((n-1)/n)*sc²

barplot(ni)
barplot(fi)
pie(ni)

#Ejercicio 2
rendimiento = datos$produccion/datos$recursos
rendA = rendimiento[datos$grupo == "A"]

#Para obtener si hay atipicos se hace boxplot
boxplot(rendA)
#Hay 5 atipicos superiores, para obtenerlos se ordena la muestra y son los 5 mayores:
sort(rendA)
#son 384.14,105.94,23,22,19

#Ejercicio 3

modelo = lm(datos$calidad ~ datos$tiempo_proceso)
#crea modelo de regresion lineal donde la var dep(Y) es datos$calidad y la indep (X) es tiempo_proceso

plot(datos$tiempo_proceso,datos$calidad,pch=16) #Pinta puntos con eje x tiempo y eje y calidad
abline(modelo,col=2,lwd=2) #Añade linea

modelo
#ordenada en el origen: 85.89. Para tiempo cero, el valor de calidad es de 85.89
#pendiente: -0.63. Por cada unidad de tiempo que se aumenta se disminuye 0.63 unidades la calidad

#Coeficiente de correlacion
cor(datos$tiempo_proceso,datos$calidad)#relacion lineal decreciente no muy fuerte (fuerte es menos de -0.7)
#cuanto mas cercano a -1 mas inverso, cuanto mas cercano a 1 mas directo

#Coeficiente de determinacion
summary(modelo)
#determinacion(multiple R-squared): 0.31, el modelo explica solo el 31% de la variabilidad de calidad mediante el tiempo del proceso, lo que es un mal ajuste

#Ejercicio 4
library(LearningStats)
Mean.CI(datos$presion, conf.level = 0.97)
#estimacion puntual (sample mean): 2.44385 units
#IC(mu): (2.36894 , 2.51876) units

#Ejercicio 5:
#H0: #H0: sigma2 <= 90^2
#Ha: sigma2 > 90^2
?variance.test()
variance.test(x=datos$produccion, sigma02=90^2, alternative = "greater", alpha = 0.01)

#Como T_obs no esta en RR y alpha es menor que el p-valor no tenemos evidencias estadisticamente significativas para rechazar H0, porlo que no hay 
#evidencias estadisticamente significativas de que la varianza actual sea mayor que el dato historico

variance.test(x=datos$produccion, sigma02=90^2, alternative = "greater", alpha = 0.05)
#A un nivel de significacion del 5%, rechazamos H0, por lo que existen evidencias significativas en la muestra de que 
#la varianza actual es mayor que el dato historico