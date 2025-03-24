#Operacions aritmetica
2^3
2**3
#Tipos de datos en R
#Enteiros ou reais
3
class(3)

#Texto (caracter)
'abcd'
class('abcd')

#Lóxico (booleano)
TRUE
FALSE

#Asignación
x=3
y<-5
X


#Exercicio 1
#Apartado a)
t=c(0,0.25,0.5,0.75)
t
t1=seq(from=0, to=0.75,len=4);t1
t2=seq(0,0.75,by=0.25);t2
?seq #Acceder a axuda da función

length(t)
sort(t) #Ordenar de menor a maior
sort(t,decreasing=TRUE) #Ordenar de maior a menor

t^2 #Eleva elementos ao cadrado
sum(t^2)
sin(2*pi*t)
t[1]#Acceso á posicion do vector (comeza en 1)
t[-3] #Todo o vecctor salvo o 3
t[-c(3,4)] #Quitar 3 e 4
t[t>0.2]
which(t>0.2)
sqrt(t)

#Apartado b)
esp = c(83.2,82.5,83.0, 83.4,82.4,81.4,81.8,81.6)
sum(esp)/length(esp)
med=mean(esp)
med

debaixo=esp[esp<med]
debaixo
which(esp<med)

enriba=esp[esp>med]
enriba
which(esp>med)

#Apartado c)

f1=1:4
f2=5:8
f3=9:12
f4=13:16
A=rbind(f1,f2,f3,f4);A

c1=c(1,5,9,13)
c2=c(2,6,10,14)
c3=c(3,7,11,15)
c4=c(4,8,12,16)
cbind(c1,c2,c3,c4)

matrix(1:16,nrow=4,ncol=4,byrow=TRUE)
B=matrix(1:16,nrow=4,ncol=4)
B

#Acceso a elementos da matriz
A[2,3]
A[2:4,c(3,4)]

#operacions ccon matrices
A+B
A-B
A*B #Produto elemento a elemento
C = A%*%B #Produto matricial
C
det(C)
solve(C) #Inversa non existe porque det=0
autoval = eigen(C)$values #Autovalores e autovecrtores

sum(autoval)

prod(autoval)
sum(diag(C))

#Exercicio 2
lista=list(nomes=c("Juan", "Josefina"), fillos=3, idade=c(16,11,4), 
           enquisa=matrix(c(8,3,7,5,5,10,4,7,4,7),nrow=5,ncol=2,byrow=T))
lista
lista$idade
lista[[3]]

#Exercicio 3
datos=data.frame(hec=c(0.8, 1.1, 0.6, 3.2, 1.4, 2.1,1.5, 0.2,1.0,6.1), 
                 ocupacion= c(1200,650, 1060,235,1300,300,750,150,440,500))
datos
class(datos)
plot(datos$hec,datos$ocupacion, main="Diagramas de dispersión",
     xlab="Hectareas",
     ylab="Ocupación",
     pch=16,
     col = "purple")

datos$zona=c(1,1,1,2,3,2,3,3,3,2)
datos

plot(datos$hec,datos$ocupacion, main="Diagramas de dispersión",
     xlab="Hectareas",
     ylab="Ocupación",
     pch=16,
     col = datos$zona)

#Exercicio 4 
letras=function(n){
  aux=sample(letters,size=n,replace=T)
  res=paste(aux,collapse="")
  return(res)
}
letras(34)

#Exercicio 5
install.packages("LearningStats") #Instalar o paquete 1 vez por ordenador
library(LearningStats)

#Exercicio 6

dat=read.table("ige.csv", header=T, sep=",",dec=".")
dat
head(dat)







