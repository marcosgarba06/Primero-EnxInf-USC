#Ejercicio 1
ns = 500 #numero de muestras
mu = 5 #Media de la distribucion 
sigma = 1 #Desviacion tipica de la distribución
n = 10 #tamaño 1 de la muestra

# Para almacenar los datos, por eficiencia, usamos una matriz. Da igual que esten en fila o en columna
# rnorm(nº datos, media, desviación típica) 
# rnorm genera n valores aleatorios de una distribución normal con media y desviación estándar dadas. 
# Se hace n*ns porque queremos que haya 500 muestras de n elemenos
x = matrix(rnorm(n*ns, mean = mu, sd = sigma), nrow = n, ncol = ns); x

# Usamos el comando apply para hacer la media y la cuasidesviación
# apply añade elementos a una matriz/data frame haciendo una funcion determinda
# apply(datos, [1 == filas, 2 == columnas], función)
media = apply(x, 2, mean)
sc = apply(x, 2, sd)

# Calculamos el estadistico de las T de Student
est = (media-mu)/(sc/sqrt(n))

# Creamos un histograma para comprobar que es una campana como una T de student
hist(est, freq = F)  #freq false para poder superponer la curva

# Usamos la función density para "discretizar" el histograma y comprobar que en efecto es una T de student
hist(est, freq = F, ylim = c(0, 0.4))
lines(density(est), col = 2, lwd = 2)

par(mfrow=c(2,2)) #Para mostrar un 2x2 de graficas

# Bucle para todos los tamaños muestrales que pide:
n = c(10, 20, 100, 500)
for (i in 1:length(n)) {
  x = matrix(rnorm(n[i]*ns, mean = mu, sd = sigma), nrow = n[i], ncol = ns); x
  
  media = apply(x, 2, mean)
  sc = apply(x, 2, sd)
  
  est = (media-mu)/(sc/sqrt(n[i])) #Estadistico T de Student
  
  hist(est, freq = F, ylim = c(0, 0.4)) #Crea histograma
  lines(density(est), col = 2, lwd = 2) #Superpone la linea
  xseq = seq(min(est), max(est), len = 1000)
  lines(xseq, dt(xseq, df = n[i] - 1), lwd = 2, col = 4) 
  #dt evalúa la funcion de densidad de la distribución t de Student en la secuencia 
  # dt(puntos, grados de libertad)
}
par(mfrow=c(1,1))

#Ejercicio 2
# X == "Tiempo de respuesta" (ms)
# X€N(μ, σ²)
# IC(μ) a nivel de confianza de 92% con σ² descoñecida

# Paquete LearningStats para calcular intervalos
install.packages("LearningStats")
library(LearningStats)

#Intervalo: x̄ ± t_n-1,1-𝜶/2 * (s_c/sqrt(n)) para que 1-𝜶 = 0.929
x = c(12.5, 13.2, 11.8, 12.9, 13.5, 12.2, 11.9, 12.7, 13.1, 12.4)
med=mean(x) #Calcula media
vari=var(x)*(n-1)/n #calcula s²
cuasivar=var(x) #Calcula sc²
# Usamos la función Mean.CI(muestra, nivel de confianza) para calcular el intervalo
Mean.CI(x, conf.level = 0.92)

#Ejercicio 3
# X_A == "Tiempo de respuesta del servidor A (s)"
# X_B == "Tiempo de respuesta del servidor B (s)"
# X_A y X_B independientes
# X_A€N(u_A, o²_A); X_B€N(u_B, o²_B)

nA = 15; medA = 120; varA = 25
nB = 12; medB = 130; varB = 30
?diffmean.CI

# Intervalos de confianza para la diferencia de dos medias
# Hacemos sqrt ya que necesitamos S e non S²
diffmean.CI(x1 = medA, x2 = medB, n1 = nA, n2 = nB, s1 = sqrt(varA), s2 = sqrt(varB), conf.level = 0.95)


# Ejercicio 4

ns = 500
n = 100
prob = 0.7
x = matrix(rbinom(ns*n, size = 1, prob = prob), nrow = n, ncol = ns)  #Crea matriz muestras
prop = apply(x, 2, mean) #Calcula la propocion de cada muestra y la añade a la matriz
hist(prop, freq = F) 
lines(density(prop), lwd = 2, col = 2)

# Secuencia de valores donde se evalua f(x), para dibujar la linea correcta
xseq = seq(min(prop), max(prop), len = 1000)
lines(xseq, dnorm(xseq, mean = prob, sd = sqrt(prob * (1-prob)/n)), col = 4, lwd = 2)

# Ejercicio 5
## X === "Estar satisfecho con la aplicación"
# X€Ber(p)
# n = 200; exitos = 150
# x̄ =150/200
# Calcular (^p +- z_1-\alpha/2 * sqrt(^p(1-^p)/n))
n = 200
exitos = 150
proportion.CI(x = exitos, n = n, conf.level = 0.95)


#Ejercicio 6
# X === "Detectouse coma un acceso sospeitoso no método 1"
# Y === "Detectouse coma un acceso sospeitoso no método 2"
n1 = 400
x1 = 280
n2 = 350
x2 = 245

diffproportion.CI(x1 = x1, x2 = x2, n1 = n1, n2 = n2, conf.level = 0.95)

#Ejercicio 7
ns = 500 #Numero de muestras
n = c(5,10,20,50) #Tamaños
mu = 3 
sigma = 0.5
par(mfrow=c(2,2))
for (i in 1:length(n)){
  # Generamos ns muestras de tamaño n[i] de N(mu, sigma^2)
  x = matrix(rnorm(n[i]*ns,mean=mu,sd=sigma),nrow=n[i],ncol=ns)
  cuasivar = apply(x,2,var)  
  est = (n[i]-1)*cuasivar/sigma^2
  hist(est,freq=FALSE,col="grey",xlab=" ",ylab=" ",main=paste("n=",n[i]), xlim=c(0,90))
  lines(density(est),lwd=2,col=2)
  x = seq(min(est),max(est),by=0.01)
  fx = dchisq(x,df=n[i]-1)
  lines(x,fx,lwd=2,col=4)
  }

























