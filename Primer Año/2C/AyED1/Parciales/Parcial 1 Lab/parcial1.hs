-- Ejercicio 1

data Deporte = Futbol | Basket | Tenis | Valorant | Dota2 deriving (Show, Eq)
type MinJugadores = Int

minimaCantidad :: Deporte -> MinJugadores
minimaCantidad x = case x of
    Futbol -> 7
    Basket -> 8
    Tenis -> 2
    Valorant -> 16
    Dota2 -> 32

ejemplo1 = minimaCantidad Futbol


-- Ejercicio 2

type NombrePersona = String
data PracticoDeporte = Ninguna | AgregaDeporte Deporte NombrePersona PracticoDeporte deriving (Show, Eq)

deporte :: PracticoDeporte -> Deporte -> NombrePersona -> Bool
deporte x de np = case x of
    Ninguna -> False
    AgregaDeporte de2 s pd -> np == s && de == de2

ejemplo2 = deporte (AgregaDeporte Futbol "Juan Pablo" Ninguna) Futbol "Juan Pablo"


-- Ejercicio 3

type EquipoFavorito = String
data ListaAsoc a b = Vacia | Nodo a b (ListaAsoc a b) deriving Show

agregaEquipoFavorito :: ListaAsoc Deporte EquipoFavorito -> Deporte
                        -> EquipoFavorito -> ListaAsoc Deporte EquipoFavorito
agregaEquipoFavorito Vacia de ef = Nodo de ef Vacia
agregaEquipoFavorito la de ef = Nodo de ef la

ejemplo3 = agregaEquipoFavorito (Nodo Futbol "PSG" Vacia) Tenis "Nadal"


-- Ejercicio 4

data Arbol a = Hoja | Rama (Arbol a) a (Arbol a) deriving (Show, Eq)

aCuantos :: Arbol Int -> Int -> Int
aCuantos Hoja _ = 0
aCuantos (Rama a1 a a2) n | a < n = 1 + aCuantos a1 n + aCuantos a2 n
                          | otherwise = aCuantos a1 n + aCuantos a2 n

ejemplo4 = aCuantos (Rama (Rama Hoja 4 Hoja) 9 (Rama Hoja 12 Hoja)) 10