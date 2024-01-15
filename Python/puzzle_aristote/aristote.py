from Application import Application
from random import choice

class Aristote:
    def __init__(self):
        self.grille = {(x,y) : 0 for x in range(5) for y in range(5)}
        self.vide = [(3, 4), (4, 4), (4, 3), (3, 0), (4, 0), (4, 1)]
        self.lst_somme = {(5,y) : 0 for y in range(5)}
        self.btn_1 = None
        self.btn_2 = None
        for v in self.vide:
            del self.grille[v]
    
    def remplir(self, grille):
        nb = [n for n in range(1, 20)]
        for key in grille.keys():
            n =  choice(nb)
            grille[key] = n
            nb.remove(n)
        return grille

    
    def somme(self, grille):
        for y in range(5):
            somme = 0
            ligne = [(x,y) for x in range(6) if (x,y) in grille.keys()]
            for cases in ligne:
                somme += grille[cases]
            self.lst_somme[(5,y)] = somme
            
    
    def permuter(self, btn1, btn2, grille):
        x = grille[self.btn_1]
        grille[self.btn_1] = grille[self.btn_2]
        grille[self.btn_2] = x
        self.somme(grille)
        self.remplir_case()
        self.btn_1 = None
        self.btn_2 = None
    
    def jeu_fini(self):
        for somme in self.lst_somme.keys():
            if self.lst_somme[somme] != 38:
                return False
        return True
     
    ################################## partie graphique ###########################
    def creer_appli(self):
        self.appli = Application("La somme de chaque ligne doit donner 38", 900, 900)
        self.appli.quadriller(6, 5, self.callback, right_click = False)
        self.remplir_case()
        self.fini = False

        
    def callback(self, mon_bouton):
        if self.fini == False:
            if mon_bouton.identifiant in self.grille.keys():
                mon_bouton.background_color = 'red'
                if self.btn_1 is None:
                    self.btn_1 = mon_bouton.identifiant
                else:
                    self.btn_2 = mon_bouton.identifiant
                    self.permuter(self.btn_1, self.btn_2, self.grille)
                    if self.jeu_fini():
                        self.fini = True
                        self.appli.title = "Well Done!"
                        self.appli.popup("mes_images/well_done.jpg")
    
    
    def remplir_case(self):
        for case in self.grille.keys():
            btn = self.appli.boutons[case]
            btn.background_color = [1,1,1,1]
            btn.text = str(self.grille[btn.identifiant])
        for case in self.lst_somme.keys():
            btn = self.appli.boutons[case]
            btn.text = str(self.lst_somme[btn.identifiant])
            btn.color = 'lightgreen'
        




a = Aristote()
grille = a.grille
a.remplir(grille)
a.somme(grille)


a.creer_appli()
a.appli.run()