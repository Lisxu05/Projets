def creer_plateau(n):
    """renvoie le dictionnaire correspondant aux lampes qui sont toutes allumés."""
    plateau = {}
    for x in range(n):
        for y in range(n):
            plateau[(x,y)] = 1
    return plateau


def a_changer(ma_case, plateau):
    """renvoie la liste des coordonées des cases à changer."""
    x, y = ma_case
    c = [(x-1, y), (x, y), (x+1, y), (x,y-1), (x,y+1)]
    changer = [coordonee for coordonee in c if coordonee in plateau.keys()]
    return changer

def resolu(plateau):
    for cle in plateau.keys():
        if plateau[cle] != 0 :
            return False
    return True