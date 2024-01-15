from kivy.app import App # Pour pouvour créer une application
from kivy.uix.floatlayout import FloatLayout # Pour créer un conteneur de type Floatlayout
from kivy.config import Config # Pour redimensionner la fenêtre
from kivy.uix.button import Button # Pour créer des boutons
from kivy.uix.label import Label # Pour afficher du texte 
from kivy.uix.togglebutton import ToggleButton # Pour avoir des boutons de sélection
from kivy.uix.image import Image # Pour intégrer des images
from kivy.uix.popup import Popup # Pour créer des fenêtre Popup
from kivy.uix.textinput import TextInput # Pour créer des zones de saisie
from kivy.config import Config

RED = [10, 0, 0, 1]
GREEN = [0, 10, 0, 1]
BLUE = [0,0,10,1]
YELLOW = [10, 10, 0, 1]
MAGENTA = [10, 0, 10, 1]
CYAN = [0, 10, 10, 1]
WHITE = [10, 10, 10, 1]
BLACK = [0, 0, 0, 1]
GREY = [1, 1, 1, 1]

class Bouton(Button):
    def __init__(self, identifiant, **kwargs):
        super().__init__(**kwargs)
        self.identifiant = identifiant
        
    def type(self, evenement):
        if self.collide_point(*evenement.pos):
            return evenement.button + "_click"# consumed touch and stop propagation / bubbling
        #return super(Bouton, self).on_touch_down(touch)
    
    def reinitialiser(self):
        self.background_normal = "atlas://data/images/defaulttheme/button"
        self.background_color = [1, 1, 1, 1]
        self.text =""
    

class Application(App):
    
    def __init__(self, title = '',largeur = 1200, hauteur = 900):
        '''Le titre est affichée en haut à gauche.
            largeur et longueur correspondent à la taille de la fenetre en pixel. 1200x 900 par défaut'''
        Config.set('graphics', 'width', str(largeur))
        Config.set('graphics', 'height', str(hauteur))
        Config.set('input', 'mouse', 'mouse,multitouch_on_demand')
        super().__init__()
        self.largeur = largeur
        self.hauteur = hauteur
        self.chemin_fond = ""
        self.boutons = {}
        self.labels = {}
        self.images = {}
        self.saisies = {}
        self.toggles = {}
        self.mes_widgets= []
        self.title = title
        self.fini = False
        self.plateau = {} # création d'un plateau de jeu

        
    def build(self):
        #self.title=self.nom
        conteneur = FloatLayout()
        if self.chemin_fond != "":
            with conteneur.canvas:
                Image(source = self.chemin_fond, size = (self.largeur, self.hauteur), pos = (0,0), allow_stretch = True)
        for element in self.mes_widgets:
            conteneur.add_widget(element)
        return conteneur
    

    def ajouter_bouton(self,identifiant = 0, **kwargs):
        '''ajoute un bouton au conteneur , l'identifiant pouvant être une chaine, un entier, un tuple'''
        mon_bouton = Bouton(identifiant, **kwargs)
        self.mes_widgets.append(mon_bouton)
        
        try:
            self.boutons[identifiant] = mon_bouton
        except:
            pass
    
    def quadriller(self, nb_boutons_largeur, nb_boutons_hauteur, fct_callback, right_click = False):
        '''Cette méthode quadrille la fenêtre de l'application avec :
                - nb_boutons_largeur en largeur
                - nb_boutons_hauteur en hauteur
                - chaque bouton ayant un id égal au tuple (x, y) de ses coordonnées
                - Le paramètre right_click à False par défaut implique la non utilisation du clic droit
                - si right_click passe à True, ajouter un paramètre evenement à la fonction callback
                - mon_bouton.type(evenement) renvoie alors "left_click" ou "right_click"
            Chaque bouton appelle la fonction callback lorsqu'on clique dessus'''
        
        for x in range(nb_boutons_largeur):
            for y in range(nb_boutons_hauteur):
                if right_click:
                    self.ajouter_bouton(identifiant=(x,y), text='',size_hint=(1/nb_boutons_largeur,1/nb_boutons_hauteur),
                                        font_size=50, pos_hint={'x': x/nb_boutons_largeur, 'y':y/nb_boutons_hauteur},
                                         on_touch_down = fct_callback)
                else:
                    self.ajouter_bouton(identifiant=(x,y), text='',size_hint=(1/nb_boutons_largeur,1/nb_boutons_hauteur),
                                        font_size=50, pos_hint={'x': x/nb_boutons_largeur, 'y':y/nb_boutons_hauteur},
                                         on_press = fct_callback)

                    
                    
    
    def ajouter_label(self, identifiant=0,**kwargs):
        mon_label = Label(**kwargs)
        mon_label.identifiant = identifiant
        self.mes_widgets.append(mon_label)
        try:
            self.labels[identifiant] = mon_label
        except:
            pass

    def ajouter_saisie(self,identifiant=0, **kwargs):
        ma_zone = TextInput(**kwargs)
        ma_zone.identifiant = identifiant
        self.mes_widgets.append(ma_zone)
        try:
            self.saisies[identifiant] = ma_zone
        except:
            pass
    
    def ajouter_image(self,identifiant=0, **kwargs):
        mon_image = Image(**kwargs)
        mon_image.identifiant = identifiant
        self.mes_widgets.append(mon_image)
        try:
            self.images[identifiant] = mon_image
        except:
            pass
    
    def ajouter_toggle(self,identifiant=0, **kwargs):
        mon_bouton_toggle = ToggleButton(**kwargs)
        mon_bouton_toggle.identifiant = identifiant
        self.mes_widgets.append(mon_bouton_toggle)
        try:
            self.toggles[identifiant] = mon_bouton_toggle
        except:
            pass
    
    def ajouter_fond(self, chemin_image):
        self.chemin_fond = chemin_image
    
    def popup(self, image):
        pop=Popup(title="", size_hint=(1, 1))
        fond=Image(source=image,pos_hint={'x':0,'y':0})
        pop.add_widget(fond)
        pop.open()       
