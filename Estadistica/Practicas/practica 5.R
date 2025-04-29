#Practica Final
#1
#X: "Prefiren a proba escrita"
#X \in Ber(P)

n=72
exitos = 41
#H0: p <= 0.5
#Ha: p>0.5

install.packages("LearningStats")

library(LearningStats)
proportion.test(x=exito,n=n, p0=0.5,alternative = "grater", alpha=0.1)
#altenative puede ser = left, = grater, =two.sided

#Non existen evidencias estatisticamente significativas para afirmar que a maioría do alumnado prefire a proba escrita
#Obtenido de la ejecución p-value=0,1193 es el valor del area das rexións de rexeitamento
#Se p.valor < \alpha rexeirtamos H0, se p-valor >= \alpha non rexeitamos H0

#Ejercicio 2
#X:"Puntuación escala Snellen de agudeza visual"
#X \in N(mu,sigma²)
#Contraste para a media(mu)
#H0: mu<=0.55
#Ha: mu > 0.55
x = c(0.71,0.66,0.64,0.49,0.80,0.67,0.52,0.81,0.55,0.65)
mu0 = 0.55
Mean.test(x=x, mu=mu0 ,alternative = "greater", alpha = 0.1)
#Existen evidencias estatísticas significativas de que a puntuación media é superoior a 0.55

#3
#X: "Tempo de vida do sistema de ventilacion" (anos)
#X \in N(mu,sigma²)
#Contraste sonbre a varianza
#H0: sigma² = 0.5
#Ha: sigma² != 0.5
mostra = c(9.9, 8.7,10.2,10.5,9.6,9.2,9.8,10.9,9.8)
sigma02= 0.5
variance.test(x=mostra, sigma02=0.5, alternative = "two.sided", alpha = 0.01)
#Tobs \not_in RR && valor > alpha =0.01, esto implica non rechazamos H0
#Non existen evidencias estatiticamente significativas de que a varianza dos tempos de vida
#difira 0.5, é dicir podemos asumir que sigma²=0.5 anos

#4
#X1:"Tempo de execución do algoritmo A"
#X2"  "     "    "       "    "      B"

A= c(12.3,15.4,21.7,17.2,38.8,42.1,10.54,23.3,35.6,28.4)
B= c(21.2,18.6,25.1,14.7,52.3,65.2,40.8,43.4,35.6,42.0)
#H0: 
#Ha:
diffmean.test(x1=A,x2=B, pounded=F,var.equal=T, alternative=)
