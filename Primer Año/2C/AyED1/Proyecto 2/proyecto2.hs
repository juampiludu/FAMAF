-- 1)

-- a)

data Carrera = Matematica | Fisica | Computacion | Astronomia

-- b)

titulo :: Carrera -> String
titulo c = case c of Matematica -> "Licenciatura en Matemática"
                     Fisica -> "Licenciatura en Física"
                     Computacion -> "Licenciatura en Ciencias de la Computación"
                     Astronomia -> "Licenciatura en Astronomía"


-- 2)

-- a)

-- data Carrera = Matematica | Fisica | Computacion | Astronomia deriving (Eq, Ord, Show)


-- 3)

-- a)

type Ingreso = Int

data Cargo = Titular | Asociado | Adjunto | Asistente | Auxiliar deriving Show
data Area = Administrativa | Ensenanza | Economica | Postgrado

data Persona = Decano
             | Docente Cargo
             | NoDocente Area
             | Estudiante Carrera Ingreso

-- b)

-- El tipo de constructor de Docente es Cargo

isCargo :: Cargo -> Persona -> Bool
isCargo Titular (Docente Titular) = True
isCargo Asociado (Docente Asociado) = True
isCargo Adjunto (Docente Adjunto) = True
isCargo Asistente (Docente Asistente) = True
isCargo _ _ = False

-- c)

cuantos_doc :: [Persona] -> Cargo -> Int
cuantos_doc [] _ = 0
cuantos_doc ((Docente s):xs) c = if isCargo c (Docente s) then 1 + cuantos_doc xs c else cuantos_doc xs c
cuantos_doc (x:xs) c = cuantos_doc xs c

-- d)

cuantos_doc' :: [Persona] -> Cargo -> Int
cuantos_doc' xs c = length (filter (isCargo c) xs)


-- 4)

-- a)

primerElemento :: [a] -> Maybe a
primerElemento [] = Nothing
primerElemento (x:xs) = Just x


-- 5)

data Cola = VaciaC | Encolada Persona Cola

-- a)

-- 1)

atender :: Cola -> Maybe Cola
atender x = case x of
    VaciaC -> Nothing
    Encolada per co -> Just co

-- 2)

encolar :: Persona -> Cola -> Cola
encolar = Encolada

-- 3)

busca :: Cola -> Cargo -> Maybe Persona
busca VaciaC _ = Nothing
busca (Encolada (Docente c) s) t = if isCargo t (Docente c) then Just (Docente c) else busca s t
busca (Encolada _ s) t = busca s t

-- b)

-- Cola se parece al tipo "pegar" o ":"


-- 6)

data ListaAsoc a b = Vacia | Nodo a b (ListaAsoc a b)

type Diccionario = ListaAsoc String String
type Padron = ListaAsoc Int String

-- a)

type GuiaTelefonica = ListaAsoc String Int

-- b)

-- 1)

la_long :: ListaAsoc a b -> Int
la_long x = case x of
    Vacia -> 0
    Nodo a b la -> 1 + la_long x

-- 2)

la_concat :: ListaAsoc a b -> ListaAsoc a b -> ListaAsoc a b
la_concat Vacia c = c
la_concat (Nodo a b s) x = Nodo a b (la_concat s x)

-- 3)

la_pares :: ListaAsoc a b -> [(a, b)]
la_pares Vacia = []
la_pares (Nodo a b l) = (a, b) : la_pares l

-- 4)

la_busca :: Eq a => ListaAsoc a b -> a -> Maybe b
la_busca Vacia _ = Nothing
la_busca (Nodo a b l) c | a == c = Just b
                        | otherwise = la_busca l c

-- 5)

la_borrar :: Eq a => a -> ListaAsoc a b -> ListaAsoc a b
la_borrar _ Vacia = Vacia
la_borrar s (Nodo a b l) | s == a = la_borrar s l
                         | otherwise = Nodo a b (la_borrar s l)


-- Ejercicio 7

data Arbol a = Hoja | Rama (Arbol a) a (Arbol a)

-- a)

a_long :: Arbol a -> Int
a_long Hoja = 0
a_long (Rama a1 a a2) = 1 + a_long a1 + a_long a2

-- b)

a_hojas :: Arbol a -> Int
a_hojas x = case x of  
    Hoja -> 1 + a_hojas x
    Rama a1 a a2 -> a_hojas x

-- c)

a_inc :: Num a => Arbol a -> Arbol a
a_inc Hoja = Hoja
a_inc (Rama a1 a a2) = Rama (a_inc a1) (a + 1) (a_inc a2)

-- d)

a_map :: (a -> b) -> Arbol a -> Arbol b
a_map _ Hoja = Hoja
a_map f (Rama a1 a a2) = Rama (a_map f a1) (f a) (a_map f a2)