##############################################################
# MODELO DE EXAME DE PRACTICAS - ESTATISTICA (CURSO 2024/25) #
##############################################################

#Lectura de datos
datos=read.table("0_datos_modelo_examen.txt",header=T,sep=";",dec=".")
#Comprobacion de que se importaron correctamente
head(datos)
#Dimension da bbdd
dim(datos)

### EJERCICIO 1
#Cualitativa ordinal: nivel
nivelf=factor(datos$nivel,levels=c("bajo","medio","alto"))
ni=table(nivelf)
n=length(nivelf)
fi=ni/n
Ni=cumsum(ni)
Fi=cumsum(fi)
#Tabla de frecuencias
tab=cbind(ni,fi,Ni,Fi);tab
#Diagrama de barras
barplot(ni)
barplot(fi)
#Diagrama de sectores
pie(ni)

#Cuantitativa discreta: lote
ni=table(datos$lote)
n=length(datos$lote)
fi=ni/n
Ni=cumsum(ni)
Fi=cumsum(fi)
#Tabla de frecuencias
tab=cbind(ni,fi,Ni,Fi);tab
#Algunas medidas caracteristicas
mean(datos$lote);sd(datos$lote);var(datos$lote)
#Diagrama de barras
barplot(fi)
#Diagrama de sectores
pie(ni)


### EJERCICIO 2
rendimiento=datos$produccion/datos$recursos
rendA=rendimiento[datos$grupo=="A"]
#Deteccion de atipicos
boxplot(rendA) #hay 5 at?picos superiores
#Identificacion de los atipicos
sort(rendA)
#los at?picos son: 19.0738255  22.7375566  23.0047170 105.9375000 384.1428571

### EJERCICIO 3
mod=lm(datos$calidad~datos$tiempo_proceso)
#Diagrama de dispersion junto con la recta
plot(datos$tiempo_proceso,datos$calidad,pch=16)
abline(mod,col=2,lwd=2)
#Estimaciones de los parametros
mod
#ordenada en el origen: 85.89. Para tiempo cero, el valor de calidad es de 85.89
#pendiente: -0.63. Por cada unidad de tiempo que se aumenta se disminuye 0.63 unidades la calidad
#Coeficiente de correlacion
cor(datos$tiempo_proceso,datos$calidad)#relacion lineal decreciente no muy fuerte
#Coeficiente de determinacion
summary(mod)
#determinacion: 0.31, el modelo explica solo el 31% de la variabilidad de calidad mediante el tiempo del proceso


### EJERCICIO 4
library(LearningStats)
Mean.CI(datos$presion,conf.level = 0.97)
#estimacion puntual: 2.44
#IC: (2.37,2.52)

### EJERCICIO 5
#H0: sigma2 <= 85^2
#Ha: sigma2 > 85^2
variance.test(datos$produccion,sigma02 = 90^2, alternative = "greater")
#A un nivel de significacion del 5%, rechazamos H0, por lo que existen evidencias
#significativas en la muestra de que la varianza actual es mayor que el dato historico
#Si evaluamos el contraste a un 1% tenemos que el p-valor es mayor que el nivel de 
#singifiación, por lo que no habría pruebas estadisticamente singificativas en los
#datos para rechazar la hipotesis nula, por lo que la daríamos por válida.

