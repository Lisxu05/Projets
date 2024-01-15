from outils_kivy import *
from modélisation import *

def callback(mon_bouton):
    '''fonction appelée lors du clic sur mon_bouton'''
    if not jeu.fini:
        identifiant = mon_bouton.identifiant
        case_a_changer = a_changer(identifiant, jeu.plateau)
        for case in case_a_changer:
            if jeu.plateau[case] == 1:
                jeu.boutons[case].background_color = GREY
                jeu.plateau[case] = 0
            else :
                jeu.boutons[case].background_color = YELLOW
                jeu.plateau[case] = 1
        if resolu(jeu.plateau):
            jeu.fini = True
            jeu.popup("mes_images/well_done.jpg")
        
            

n = 6
jeu = Application("LUMIÈRE")
jeu.quadriller(n,n, callback)
jeu.plateau = creer_plateau(n)
for bouton in jeu.boutons.keys():
    jeu.boutons[bouton].background_color = YELLOW


jeu.run()