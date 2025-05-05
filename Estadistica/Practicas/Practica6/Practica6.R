#Practica 6
#1
#X: "Prefiren a proba escrita"
#X \in Ber(P)

#H0: p <= 0.5
#Ha: p > 0.5
#RR = [z1-𝜶,+∞)
library(LearningStats)
n=72
exitos = 41
proportion.test(x=exitos,n=n, p0=0.5,alternative = "greater", alpha=0.1)
#altenative puede ser =less, =greater, =two.sided

#Obtenido da execución: p-valor=0,1193 que é o valor do area da rexión de rexeitamento
#p-valor = P(N(0,1)>T_obs), siendo T_obs = 1.17851
#Se p.valor<𝜶 rexeirtamos H0, se p-valor >= 𝜶 non rexeitamos H0
#Non existen evidencias estatisticamente significativas para afirmar que a maioría do alumnado prefire a proba escrita

#Ejercicio 2
#X:"Puntuación escala Snellen de agudeza visual"
#X \in N(μ, σ²)

#Contraste para a media(μ)
#H0: μ0 <= 0.55
#Ha: μ0 > 0.55
#RR: [z1-𝜶,+∞)

x = c(0.71,0.66,0.64,0.49,0.80,0.67,0.52,0.81,0.55,0.65)
mu0 = 0.55
Mean.test(x=x, mu=mu0 ,alternative = "greater", alpha = 0.1)
#Existen evidencias estatísticas significativas de que a puntuación media é superior a 0.55
#T_obs cae en la RR y p_valor < 𝜶, por tanto se rechaza H0

#Exercicio 3
#X: "Tempo de vida do sistema de ventilacion" (anos)
#X \in N(μ, σ²)
#Contraste sonbre a varianza (σ²)

#H0: sigma² = 0.5
#Ha: sigma² != 0.5
#RR: [0, X²𝜶/2] U [X²1-𝜶/2, +∞)
mostra = c(9.9, 8.7,10.2,10.5,9.6,9.2,9.8,10.9,9.8)
sigma02= 0.5
variance.test(x=mostra, sigma02=0.5, alternative = "two.sided", alpha = 0.01)
#T_obs no esta en RR && p_valor = 0.91039 > 𝜶=0.01, esto implica non rechazamos H0
#Non existen evidencias estatiticamente significativas para afirmar que a varianza do tempo de vida difira de 0.5 anos², 
#é dicir podemos asumir que sigma²=0.5 anos²

#Exercicio 4
#X1:"Tempo de execución do algoritmo A"
#X2"  "    "    "       "    "      B"
#X1 \in N(μ1, σ²)
#X2 \in N(μ2, σ²)
A= c(12.3,15.4,21.7,17.2,38.8,42.1,10.54,23.3,35.6,28.4)
B= c(21.2,18.6,25.1,14.7,52.3,65.2,40.8,43.4,35.6,42.0)
#H0: μA = μB => μA - μB = 0
#Ha: μA != μB => μA - μB != 0

diffmean.test(x1=A,x2=B, paired=F,var.equal=T, alternative= "two.sided", alpha = 0.05)
#Paired es si son independientes o no y var.equal si las varianzas son iguales
#Como p_valor>𝜶 y T_obs no esta en la RR no se rechaza H0:
#No existen evidencias estadisticamente significativas para afirmar que os tempos de execucuion son diferentes entre si.

#Exercicio 5
#A: "Tiempo de respuesta antes de la capacitacion"
#B: "  "    "      "  después  "  "      "      "
previo=c(68, 77, 94, 73, 37, 131, 77, 24, 99, 629, 116)
post=c(95, 90, 86, 58, 47, 121, 136, 65, 131, 630, 104)

#H0: μA >= μB => μA - μB >= 0
#Ha: μA < μB => μA - μB < 0

diffmean.test(x1 = previo, x2 = post, paired=T,alternative = "less",alpha = 0.01)
#T_obs no esta en RR, p_valor >= 𝜶, lo que implica que no rechazamos H0
#No existen evidencias estadísticas suficientes para afirmar que el programa de capacitación haya reducido el tiempo de respuesta de los técnicos.

#Exercicio 6:
#X1: "Usuario de red no segura afectado por malware"
#X2: "Usuario de red segura afectado por malware"
#X1 \in Ber(p1)
#X2 \in Ber(p2)
n1 = 307; exitos1 = 230
n2 = 75; exitos2 = 30

#H0: p2 >= p1 => p2 - p1 <= 0
#Ha: p2 < p1 => p2 - p1 > 0

diffproportion.test(x1=exitos2 , x2=exitos1, n1=n2 ,n2=n1 , alternative = "less", alpha = 0.01)
#Como T_obs esta en RR entonces rechazamos H0, por lo que 
#existen evidencias estadísticamente significativas de que la proporción de usuarios afectados por malware es menor en redes seguras que en redes no segura

#Ejercicio7
#X1: "Uso de CPU software A" (%)
#X2: "Uso de CPU software B" (%)
#X1 \in N(μ1, σ1²)
#X2 \in N(μ2, σ2)

A=c(34.5, 36.1, 35.9, 33.4, 34.8, 36.2, 35.6, 34.7, 35.0, 34.3, 35.1, 34.9)
B=c(27.8, 28.3, 29.0, 28.5, 28.2, 29.3, 28.7, 29.5, 28.8, 28.4, 29.1, 28.6)

#H0: σ1² = σ2²
#Ha: σ1² != σ2²

diffvariance.test(x1 = A, x2 = B, alternative = "two.sided", alpha = 0.05)

#Como T_obs no esta en RR no rechazamos H0
#No existen evidencias estadisticamente significativas de que las varianzas del uso de CPU son diferentes 




