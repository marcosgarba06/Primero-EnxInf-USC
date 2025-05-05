# Exercicio 1

# Temos 500 mostras de tamaño n = 10 onde X€N(5, 1)
# 
# x_1  y_2 ...
# ...  ... ...
# x_10 y_2 ...
# vai a dar
# t_1  t_2 ...
#
# e calculamos     _
#              T = x-u/s_c/sqrt(n), onde T€T_n-1

ns = 500 # nº de mostras
n = 10 # tamaño mostral
mu = 5; sigma = 1 # N(5, 1)

# Para almacenar os datos, por eficiencia, usamos unha matriz. Da igual que estean en fila que en columna
# rnorm(nº datos, media, desviación típica)
x = matrix(rnorm(n*ns, mean = mu, sd = sigma), nrow = n, ncol = ns); x

# Usamos o comando apply para facer media e cuasidesviación
# apply(datos, [1 === filas, 2 === columnas], funcuón)
media = apply(x, 2, mean)
sc = apply(x, 2, sd)
# Calculamos as t
est = (media-mu)/(sc/sqrt(n))
# Creamos un histograma para comprobar que é unha campana de xeito coma unha T de student
hist(est, freq = F)
# Usamos a función density para "discretizar" o histograma por cuestións que se chapan os da carreiras de mates
# e comprobar que en efecto é unha T de student
hist(est, freq = F, ylim = c(0, 0.4))
lines(density(est), col = 2, lwd = 2)

# Abrimos espazo para unha matriz 2x2 de gráficas
par(mfrow=c(2,2))
# Agora automatizando para os tamaños mostrais:
n = c(10, 20, 100, 500)
for (i in 1:length(n)) {
  x = matrix(rnorm(n[i]*ns, mean = mu, sd = sigma), nrow = n[i], ncol = ns); x
  
  media = apply(x, 2, mean)
  sc = apply(x, 2, sd)
  
  est = (media-mu)/(sc/sqrt(n[i]))
  
  hist(est, freq = F, ylim = c(0, 0.4))
  lines(density(est), col = 2, lwd = 2)
  xseq = seq(min(est), max(est), len = 1000)
  lines(xseq, dt=n[i]-1, lwd = 2, col = 4)
}
par(mfrow=c(1,1))

# Exercicio 2
# X === "Tempo de resposta (segundos)
# X€N(u, o²)
# I€(u) a nivel de confianza de 92%

# Usamos o paquete LearningStats para calcular intervalos en lugar de facerlo a man
install.packages("LearningStats")
library(LearningStats)
# Ẍ + t_n-1,1-\alpha/2 s_c/sqrt(n) para que 1 - \alpha = 0.929
x = c(12.5, 13.2, 11.8, 12.9, 13.5, 12.2, 11.9, 12.7, 13.1, 12.4)
# Usamos a función Mean.CI(mostra, nivel de confianza)
Mean.CI(x, conf.level = 0.92)

# Exercicio 3
# X_A === "Tempo de resposta do servidor A (s)"
# X_B === "Tempo de resposta do servidor B (s)"
# X_A é independente de X_B
# X_A€N(u_A, o²_A); X_B€N(u_B, o²_B)
nA = 15; medA = 120; varA = 25
nB = 12; medB = 130; varB = 30
?diffmean.CI
# Intervalos de confianza para a diferenza de dúas medias
# Facemos sqrt xa que necesitamos o e non o²
diffmean.CI(x1 = medA, x2 = medB, n1 = nA, n2 = nB, s1 = sqrt(varA), s2 = sqrt(varB), conf.level = 0.95)

# Exercicio 4
x = matrix(rbinom (500*100, size = 1, prob = 0.7), nrow = 100, ncol = 500)
media = apply(x, 2, mean)
y = matrix(rnorm (500*100, mean = 0.7, sd = 0.7*0.3/100), nrow = 100, ncol = 500)
#media2 = apply(y, 2, mean)
hist(media, ylim = c(0,100))
lines(density(y), col = 2, lwd = 2)

# Exercicio 4 resolto
ns = 500
n = 100
prob = 0.7
x = matrix(rbinom(ns*n, size = 1, prob = prob), nrow = n, ncol = ns)
prop = apply(x, 2, mean)
hist(prop, freq = F)
lines(density(prop), lwd = 2, col = 2)

# Grella de valores no eixo x onde avalias f(x)
xseq = seq(min(prop), max(prop), len = 1000)
lines(xseq, dnorm(xseq, mean = prob, sd = sqrt(prob * (1-prob)/n)), col = 4, lwd = 2)

# Exercicio 5
# X === "Estar satisfeito coa applicación"
# X€ Ber(p)
# n = 200; exitos = 150
# Ẍ = 150/200; Calcular (^p +- z_1-\alpha/2 * sqrt(^p(1-^p)/n))
n = 200
exitos = 150
proportion.CI(x = exitos, n = n, conf.level = 0.95)

# Exercicio 6
# X === "Detectouse coma un acceso sospeitoso no método 1"
# Y === "Detectouse coma un acceso sospeitoso no método 2"
n1 = 400; x1 = 280
n2 = 350; x2 = 245

diffproportion.CI(x1 = x1, x2 = x2, n1 = n1, n2 = n2, conf.level = 0.95)