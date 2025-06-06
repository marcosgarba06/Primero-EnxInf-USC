#Exercicio1

mostra=c("b","b","r","mb","m","b","b","r","mm",
         "b", "mb","mb", "r", "b", "m", "b", "mb",
         "mb", "b", "r")
#X = Grao de stisfaccion
#Cualitativa ordinal
class(mostra)

mostraf = factor(mostra,levels=c("mm", "m", "r", "b", "mb"))
#factor cinvuerte vector de caracteres en un factoor de R

mostra
mostraf

#fracuencias absolutas
ni=table(mostraf);ni
#frecuencias relativas
n=length(mostraf);n
fi=ni/n;fi
#frecuencias absolutas acumuladas
Ni=cumsum(ni);Ni
#frecuencias relativas acumuladas
Fi=cumsum(fi);Fi

#Taboa de frecuencias
taboa=cbind(ni,fi,Ni,Fi);taboa

#Representación gráfica
barplot(ni, col="purple", border= "cyan", main= "Diagrama de barras", space = 2)
#Diagrama de sectores
pie(ni, main= "Diagrama de sectores", col = rainbow(5))


#Exercicio 2

install.packages("MASS")
library(MASS)
head(quine)
?quine

#Sexo
#Cualitativa nominal
ni=table(quine$Sex)
n=length(quine$Sex)
fi=ni/n
taboa_sex=cbind(ni,fi);taboa_sex

#Idade 
#Cualitativa ordinal (completar, es como el ejercicio 1)

#Taboa de continxencia
tab=table(quine$Sex, quine$Age);tab
addmargins(tab)

#Representar Idade
barplot(table(quine$Age), col = "green", main = "Diagrama de Barras")

#Exercicio 3
head(geyser)
#Duración: cuantitativa continua
hist(geyser$duration) #Con alturas as frec absolutas
hist(geyser$duration, freq=F) #Con alturas as dendidades de frecuencias
hist(geyser$duration, freq=F, col ="darkgreen", xlab="Duration (segs)", 
     ylab="Densidade", main="Histograma", border="gray") 

#Diagrama de caixa
boxplot(geyser$duration, main="Diagrama de caixa", col ="darkblue")

#medidas caracteristicas  
summary(geyser$duration)
quantile(geyser$duration, probs=c(0.25,0.5,0.75))
quantile(geyser$duration, probs=0.1)
median(geyser$duration)

sc2=var(geyser$duration) #Cuasi-varianza
n=length(geyser$duration)
s2=((n-1)/n)*sc2 #vaianza mostral

sc2;s2

sc=sd(geyser$duration) #Cuasi-desviación
s=sqrt((n-1)/n)*sc #Desviacion tipica
sc;s
range(geyser$duration)
diff(range(geyser$duration)) #rango mostra



#Exercicio4
head(quine)
DiasF=quine$Days[quine$Sex=="F"];DiasF
DiasM=quine$Days[quine$Sex=="M"];DiasM

#variable cuantitativa discreta con moitos
#valores polo que a trataremos como unha continua
par(mfrow=c(1,2))
hist(DiasF, freq=F, ylim=c(0,0.055))
hist(DiasM, freq=F, ylim=c(0,0.055))
par(mfrow=c(1,1))

boxplot(quine$Days~quine$Sex)
boxplot(quine$Days~quine$Age)

#medidas caracteristicas para ambos grupos
summary(DiasF)
summary(DiasM)


#Exercicio 5 
head(airquality)
vento=airquality$Wind
hist(vento,breaks=4)
hist(vento, breaks=9)
hist(vento, breaks=14)
hist(vento, breaks=19)

boxplot(vento)

#Hay atipicos segundo o diagrama de caixa
sort(vento)
#Os valores mais altos son os atipicos


#Exercicio proposto

head(mtcars)
?mtcars

#mpg: cuantitativa continua
#cyl:cuantitativa discreta
#disp:cuantitativa continua
#hp: cuantitativa discreta
#drat: cuantitativa continua
#wt: cuantitativa continua
#qsec: cuantitativa continua 
#vs: cualitativa nominal
#am:  cualitativa nominal
#gear: cuantitativa discreta
#carb: cuantitativa discreta

apply(mtcars, 2, summary)

#mpg mediana=19.20 media=20.09, moda= [15,20]
hist(mtcars$mpg)
#HP
n=length(mtcars$hp);n
sc2=var(mtcars$hp);sc2 #Cuasivarianza
s2=((n-1)/n)*sc2;sc #Varianza

sc=sd(mtcars$hp);sc
s=sqrt((n-1)/n)*sc

quantile(mtcars$wt , probs=c(0.25,0.5,0.75))

hist(mtcars$mpg)
boxplot(mtcars$mpg)

boxplot(mtcars$hp)
sort(mtcars$hp) #335 e o atipico

plot(mtcars$hp, mtcars$mpg, pch=16)

#Ejemplo tabla cuantitativas continuas 
clases = cut(datos, breaks = 4, right = F)
ni = table(clases)
fi = prop.table(clases)
Ni = cumsum(fi)
Fi = cumsum(fi)
