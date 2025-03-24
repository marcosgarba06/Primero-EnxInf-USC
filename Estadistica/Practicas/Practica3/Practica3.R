###EXERCICIO 1
dat = read.table("DatosGapminder.csv", header=T, sep=",",dec="." )
head(dat)
dim(dat)

#Apartado a)
hist(dat$PCs)
boxplot(dat$PCs)


#Apartado b)
n=length(dat$PCs);n
var(dat$PCs)*((n-1)/n) #Varianza
sqrt(var(dat$PCs)*((n-1)/n)) #desiacion tipica
sd(dat$PCs)*sqrt((n-1)/n)

#Apartado c)
quantile(dat$PCs,probs=c(0.3,0.6,0.9))

#Apartado d)
med=mean(dat$PCs)
desv=sd(dat$PCs)*sqrt((n-1)/n)
PCS_tip=(dat$PCs-med)/desv
mean(PCS_tip) #ten media 0
sd(PCS_tip)*sqrt((n-1)/n) #des tipica 

#Apartado e)
hist(dat$GDP)
boxplot(dat$GDP)
val_atip=sort(dat$GDP)[173:177] #Valores dos atípicos
pos=which(dat$GDP%in%val_atip)
dat$Paises[pos]

var(dat$GDP)*((n-1)/n) #Varianza
sqrt(var(dat$GDP)*((n-1)/n)) #desiacion tipica
sd(dat$GDP)*sqrt((2-1)/n)

quantile(dat$GDP,probs=c(0.3,0.6,0.9))

med2=mean(dat$GDP)
desv2=sd(dat$GDP)*sqrt((n-1)/n)
GDP_tip=(dat$GDP-med2)/desv2
mean(GDP_tip) #ten media 0
sd(GDP_tip)*sqrt((n-1)/n) #des tipica 


###Exercicio 2
#Apartado a)
y=dat$GDP #var resposta ou dependente
x=dat$PCs #var explicativa ou indep

plot(x,y,main="Diagrama de dispersion", xlab="PCs", ylab="PIB", pch=16, cex=1.2)

#Apartado b)
cov(x,y)
cor(x,y)
#relacion directa(signo positivo) e bastante forte pola correlacion cercana a 1

#Apartado c)
mod=lm(y~x)
mod
#y=-3032.6 + 446.6*x

abline(mod,col=2,lwd=2)

#Apartado d)
summary(mod)
#R^2=0.6

#Apartado e)
res=mod$residuals
res
plot(x,res,pch=16,cex=1.2)
abline(h=0)

#Apartado f)
summary(x)
#5, 25 e 75 estan  no rango polo que podemos facer pred
predict(mod,newdata = data.frame(x=c(5,25,75)))
#Apartado g)
UE=c("Austria", "Belgium", "Bulgaria", "Croatia", "Republic of Cyprus",
      "Czech Republic", "Denmark", "Estonia", "Finland", "France", "Germany",
      "Greece", "Hungary", "Ireland", "Italy", "Latvia", "Lithuania",
      "Luxembourg", "Malta", "Netherlands", "Poland", "Portugal", "Romania",
      "Slovakia", "Slovenia", "Spain", "Sweden")

filas=which(dat$Paises%in%UE)
datUE=dat[filas, ]
dim(datUE)
head(datUE)
setdiff(UE,dat$Paises) #Paises da Ue que non estan na base de datos orixinal
plot(datUE$PCs, datUE$GDP, pch=16, cex=1.2)

xx=datUE$PCs
mod2=lm(datUE$GDP~xx)
mod2
abline(mod2,lwd=2,col=2)

predict(mod2, newdata = data.frame(xx=c(75))) #5 e 25 non estan no rango de valores para PCs na UE

###Exercicio3
library(MASS)
head(geyser)
y= geyser$waiting #var resposta ou dependente
x= geyser$duration #var explicativa ou indep

plot(x,y,main="Diagrama de dispersion", xlab="PCs", ylab="PIB", pch=16, cex=1.2)

cov(x,y)
cor(x,y)
#relacion inversa medianamente forte

mod=lm(y~x)
mod
#y=99.31 + -7.80*x

abline(mod,col=2,lwd=2)

summary(mod)
#R^2=0.4155 bastante baixo

res=mod$residuals
res
plot(x,res,pch=16,cex=1.2)
abline(h=0)

predict(mod,newdata = data.frame(x=c(4.3,2.3))) #Non se pode facer prediccion en 7


















