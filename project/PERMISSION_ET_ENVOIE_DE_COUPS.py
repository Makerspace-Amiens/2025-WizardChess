# Plateau d'échecs avec placement initial des pièces
#import envoie message vers arduino
import serial
arduino = serial.Serial(port='COM3', baudrate=9600, timeout=1)
time.sleep(2)  # Attendre que l'Arduino soit prêt

plateau = [
    ["♜", "♞", "♝", "♛", "♚", "♝", "♞", "♜"],  # Rangée 8 - Noirs
    ["♟", "♟", "♟", "♟", "♟", "♟", "♟", "♟"],  # Rangée 7 - Pions noirs
    [" ", " ", " ", " ", " ", " ", " ", " "],  # Rangée 6
    [" ", " ", " ", " ", " ", " ", " ", " "],  # Rangée 5
    [" ", " ", " ", " ", " ", " ", " ", " "],  # Rangée 4
    [" ", " ", " ", " ", " ", " ", " ", " "],  # Rangée 3
    ["♙", "♙", "♙", "♙", "♙", "♙", "♙", "♙"],  # Rangée 2 - Pions blancs
    ["♖", "♘", "♗", "♕", "♔", "♗", "♘", "♖"]   # Rangée 1 - Blancs
]
def mouvements_pion(x, y):
    pion = plateau[x][y]
    mouvements = []

    if pion == "♙":  # Pion blanc
        if x > 0 and plateau[x-1][y] == " ":
            mouvements.append((x-1, y))
            if x == 6 and plateau[x-2][y] == " ":
                mouvements.append((x-2, y))
        if x > 0 and y > 0 and plateau[x-1][y-1] in "♟♜♞♝♛♚":
            mouvements.append((x-1, y-1))
        if x > 0 and y < 7 and plateau[x-1][y+1] in "♟♜♞♝♛♚":
            mouvements.append((x-1, y+1))

    elif pion == "♟":  # Pion noir
        if x < 7 and plateau[x+1][y] == " ":
            mouvements.append((x+1, y))
            if x == 1 and plateau[x+2][y] == " ":
                mouvements.append((x+2, y))
        if x < 7 and y > 0 and plateau[x+1][y-1] in "♙♖♘♗♕♔":
            mouvements.append((x+1, y-1))
        if x < 7 and y < 7 and plateau[x+1][y+1] in "♙♖♘♗♕♔":
            mouvements.append((x+1, y+1))

    return mouvements

def mouvements_cavalier(x, y):
    piece = plateau[x][y]
    directions = [(-2, -1), (-2, 1), (-1, -2), (-1, 2),
                  (1, -2), (1, 2), (2, -1), (2, 1)]
    ennemis = "♟♜♞♝♛♚" if piece == "♘" else "♙♖♘♗♕♔"
    mouvements = []

    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < 8 and 0 <= ny < 8:
            cible = plateau[nx][ny]
            if cible == " " or cible in ennemis:
                mouvements.append((nx, ny))
    return mouvements

def mouvements_roi(x, y):
    piece = plateau[x][y]
    ennemis = "♟♜♞♝♛♚" if piece == "♔" else "♙♖♘♗♕♔"
    mouvements = []

    for dx in [-1, 0, 1]:
        for dy in [-1, 0, 1]:
            if dx == dy == 0:
                continue
            nx, ny = x + dx, y + dy
            if 0 <= nx < 8 and 0 <= ny < 8:
                cible = plateau[nx][ny]
                if cible == " " or cible in ennemis:
                    mouvements.append((nx, ny))
    return mouvements

def mouvements_ligne(x, y, directions, ennemis):
    mouvements = []
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        while 0 <= nx < 8 and 0 <= ny < 8:
            cible = plateau[nx][ny]
            if cible == " ":
                mouvements.append((nx, ny))
            elif cible in ennemis:
                mouvements.append((nx, ny))
                break
            else:
                break
            nx += dx
            ny += dy
    return mouvements

def mouvements_tour(x, y):
    piece = plateau[x][y]
    ennemis = "♟♜♞♝♛♚" if piece == "♖" else "♙♖♘♗♕♔"
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    return mouvements_ligne(x, y, directions, ennemis)

def mouvements_fou(x, y):
    piece = plateau[x][y]
    ennemis = "♟♜♞♝♛♚" if piece == "♗" else "♙♖♘♗♕♔"
    directions = [(-1, -1), (-1, 1), (1, -1), (1, 1)]
    return mouvements_ligne(x, y, directions, ennemis)

def mouvements_reine(x, y):
    piece = plateau[x][y]
    ennemis = "♟♜♞♝♛♚" if piece == "♕" else "♙♖♘♗♕♔"
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1),  # Tour
                  (-1, -1), (-1, 1), (1, -1), (1, 1)]  # Fou
    return mouvements_ligne(x, y, directions, ennemis)


def coord_to_case(x, y):
    """Convertit (x, y) en notation échiquéenne (ex: (6, 4) → E2)"""
    colonne = chr(ord('A') + y)
    ligne = str(8 - x)
    return colonne + ligne

# Stockage des mouvements avec noms de cases
mouvements_blancs = []
mouvements_noirs = []

for x in range(8):
    for y in range(8):
        piece = plateau[x][y]
        if piece == " ":
            continue

        if piece in "♙♘♖♗♕♔":
            couleur = "blanc"
        else:
            couleur = "noir"

        if piece in "♙♟":
            mouvements = mouvements_pion(x, y)
        elif piece in "♘♞":
            mouvements = mouvements_cavalier(x, y)
        elif piece in "♖♜":
            mouvements = mouvements_tour(x, y)
        elif piece in "♗♝":
            mouvements = mouvements_fou(x, y)
        elif piece in "♕♛":
            mouvements = mouvements_reine(x, y)
        elif piece in "♔♚":
            mouvements = mouvements_roi(x, y)
        else:
            mouvements = []

        for dest_x, dest_y in mouvements:
            de_case = coord_to_case(x, y)
            vers_case = coord_to_case(dest_x, dest_y)
            if couleur == "blanc":
                mouvements_blancs.append((de_case, vers_case))
            else:
                mouvements_noirs.append((de_case, vers_case))

# Affichage
print("Mouvements possibles des pions blancs :")
for move in mouvements_blancs:
    print(f"De {move[0]} à {move[1]}")

print("\nMouvements possibles des pions noirs :")
for move in mouvements_noirs:
    print(f"De {move[0]} à {move[1]}")

## Execution du jeu avec mouvements aléatoires
import random
import time

def afficher_plateau():
    print("  A B C D E F G H")
    for i, ligne in enumerate(plateau):
        print(8 - i, end=" ")
        for case in ligne:
            print(case if case != " " else ".", end=" ")
        print()
    print()

def case_to_coord(case):
    colonne = ord(case[0].upper()) - ord('A')
    ligne = 8 - int(case[1])
    return (ligne, colonne)

def coord_to_case(x, y):
    return chr(ord('A') + y) + str(8 - x)

def appliquer_mouvement(move):
    (x1, y1), (x2, y2) = move
    piece = plateau[x1][y1]
    plateau[x1][y1] = " "
    plateau[x2][y2] = piece

def obtenir_mouvements(joueur):
    mouvements = []
    for x in range(8):
        for y in range(8):
            piece = plateau[x][y]
            if piece == " ":
                continue
            if joueur == "blanc" and piece not in "♙♘♖♗♕♔":
                continue
            if joueur == "noir" and piece not in "♟♞♜♝♛♚":
                continue
            if piece in "♙♟":
                deplacements = mouvements_pion(x, y)
            elif piece in "♘♞":
                deplacements = mouvements_cavalier(x, y)
            elif piece in "♖♜":
                deplacements = mouvements_tour(x, y)
            elif piece in "♗♝":
                deplacements = mouvements_fou(x, y)
            elif piece in "♕♛":
                deplacements = mouvements_reine(x, y)
            elif piece in "♔♚":
                deplacements = mouvements_roi(x, y)
            else:
                continue
            for dest in deplacements:
                mouvements.append(((x, y), dest))
    return mouvements

def jouer_coup_ordinateur_intelligent(joueur):
    """Retourne un coup de l'ordinateur basé sur des priorités simples : capturer > sécurité."""
    mouvements_possibles = obtenir_mouvements(joueur)
    ennemi = "blanc" if joueur == "noir" else "noir"

    # 1. Coups qui capturent une pièce adverse
    coups_captures = []
    for (x1, y1), (x2, y2) in mouvements_possibles:
        piece_cible = plateau[x2][y2]
        if piece_cible != " ":
            coups_captures.append(((x1, y1), (x2, y2)))
    if coups_captures:
        return random.choice(coups_captures)

    # 2. Coups sûrs : éviter de se faire capturer juste après
    coups_surs = []
    for (x1, y1), (x2, y2) in mouvements_possibles:
        piece = plateau[x1][y1]
        sauvegarde_source = plateau[x1][y1]
        sauvegarde_dest = plateau[x2][y2]
        # simuler le coup
        plateau[x1][y1] = " "
        plateau[x2][y2] = piece
        menaces_adverses = obtenir_mouvements(ennemi)
        est_menace = any((x2, y2) == to for _, to in menaces_adverses)
        # annuler simulation
        plateau[x1][y1] = sauvegarde_source
        plateau[x2][y2] = sauvegarde_dest
        if not est_menace:
            coups_surs.append(((x1, y1), (x2, y2)))

    if coups_surs:
        return random.choice(coups_surs)

    # 3. Sinon, n'importe quel coup
    return random.choice(mouvements_possibles)

i=0#compteur pour savoir qui joue
# --- CHOIX DU JOUEUR ---
while True:
    choix = input("Voulez-vous jouer les blancs ou les noirs ? (blanc/noir) : ").strip().lower()
    if choix in ["blanc", "noir"]:
        humain = choix
        ordinateur = "noir" if humain == "blanc" else "blanc"
        if humain=="blanc":
            i=1
        else:
            i=0
        break
    print("Réponse invalide. Tapez 'blanc' ou 'noir'.")

afficher_plateau()

# --- BOUCLE DE JEU ---
while True:
    if i==0:# Tour de l'ordinateur
        print(f"\nL'ordinateur ({ordinateur}) réfléchit...")
        time.sleep(1)

        coups_ordi = obtenir_mouvements(ordinateur)
        if not coups_ordi:
            print(f"{ordinateur.capitalize()} ne peut plus jouer. Partie terminée.")
            break

        coup = jouer_coup_ordinateur_intelligent(ordinateur)
        de_case = coord_to_case(*coup[0])
        vers_case = coord_to_case(*coup[1])
        print(f"Ordinateur joue : {de_case + vers_case}")
        appliquer_mouvement(coup)
        afficher_plateau()
        arduino.write((de_case + vers_case + '\n').encode())  # Encoder et ajouter \n
        time.sleep(15)  # Attendre que l'Arduino réponde #envoyer la chaine de code ici
        i=1-i
    else:
        # Tour du joueur humain
        coups_humain = obtenir_mouvements(humain)
        if not coups_humain:
            print(f"{humain.capitalize()} ne peut plus jouer. Partie terminée.")
            break

        while True:
            coup_txt = input(f"Votre coup ({humain}, format E2E4) : ").strip().upper()
            if len(coup_txt) == 4:
                try:
                    origine = case_to_coord(coup_txt[:2])
                    destination = case_to_coord(coup_txt[2:])
                    if ((origine, destination)) in coups_humain:
                        appliquer_mouvement((origine, destination))
                        afficher_plateau()
                        arduino.write((de_case + vers_case + '\n').encode())  # Encoder et ajouter \n
                        time.sleep(15)  # Attendre que l'Arduino réponde envoyer la chaine de code ici
                        i = 1 - i  # On change de joueur seulement ici
                        break
                    else:
                        print("Coup invalide. Réessayez.")
                except:
                    print("Format incorrect. Réessayez.")
            else:
                print("Format invalide. Entrez un coup comme E2E4.")

