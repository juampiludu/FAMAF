data Color = Rojo|Amarillo|Azul|Verde deriving(Show,Eq)
data Forma = Triangulo|Cuadrado|Rombo|Circulo deriving(Show,Eq)
type Figura = (Forma, Color, Int)

-- 1)

rojo :: Figura -> Bool
rojo (f,c,t) = c == Rojo

azul :: Figura -> Bool
azul (f,c,t) = c == Azul

amarillo :: Figura -> Bool
amarillo (f,c,t) = c == Amarillo

verde :: Figura -> Bool
verde (f,c,t) = c == Verde

circulo :: Figura -> Bool
circulo (f,c,t) = f == Circulo

rombo :: Figura -> Bool
rombo (f,c,t) = f == Rombo

cuadrado :: Figura -> Bool
cuadrado (f,c,t) = f == Cuadrado

triangulo :: Figura -> Bool
triangulo (f,c,t) = f == Triangulo

-- 2)

tam :: Figura -> Int
tam (f,c,t) = t


-- 3)

-- a) Todas las figuras de xs son rojas.

-- < ∀x : x ∈l xs : rojo.x >
-- < ∀x : True : x ∈l xs => rojo.x >


-- b) Todas las figuras de xs son de tamaño menor a 5.

-- < ∀x : x ∈l xs : tam.x < 5 >
-- < ∀x : True : x ∈l xs => tam.x < 5 >


-- c) Todos los triángulos de xs son rojos.

-- < ∀x : x ∈l xs ∧ triangulo.x : rojo.x >
-- < ∀x : : x ∈l xs ∧ triangulo.x => rojo.x >


-- d) Existe un cuadrado verde en xs.

-- < ∃x : x ∈l xs ∧ cuadrado.x : verde.x >
-- < ∃x : x ∈l xs ∧ verde.x : cuadrado.x >
-- < ∃x : x ∈l xs : verde.x ∧ cuadrado.x >
-- < ∃x : : x ∈l xs ∧ cuadrado.x ∧ verde.x >


-- e) Todos los círculos de xs son azules y de tamaño menor a 10.

-- < ∀x : x ∈l xs : azul.x ∧ tam.x < 10 >


-- f) Ningún triángulo de xs es azul.

-- < ∀x : x ∈l xs : triangulo.x /= azul.x >


-- g) En xs no hay círculos amarillos ni verdes.

-- < ∀x : x ∈l xs : circulo.x /= amarillo.x ∨ verde.x >


-- h) Existe (al menos) un cuadrado de tamaño menor a 5 en xs.

-- < ∃x : x ∈l xs ∧ cuadrado.x : tam.x < 5 >


-- i) Si hay círculos rojos en xs, entonces hay cuadrados rojos.

-- < ∀x : : x ∈l xs ∧ circulo.x ∧ rojo.x => cuadrado.x ∧ rojo.x >



-- 4)

-- a)

-- xs= [(Triangulo,Rojo,5),(Cuadrado,Rojo,10),(Circulo,Rojo,2)]
-- xs′= [(Cuadrado,Azul,15),(Circulo,Rojo,1),(Triangulo,Azul,2)]


-- b)

-- xs= [(Triangulo,Rojo,2),(Cuadrado,Rojo,1),(Circulo,Rojo,4)]
-- xs′= [(Cuadrado,Azul,15),(Circulo,Rojo,1),(Triangulo,Azul,2)]


-- c)

-- xs= [(Triangulo,Rojo,5),(Cuadrado,Rojo,10),(Circulo,Rojo,2)]
-- xs′= [(Cuadrado,Azul,15),(Triangulo,Verde,1),(Triangulo,Azul,2)]


-- d)

-- xs= [(Triangulo,Rojo,5),(Cuadrado,Verde,10),(Circulo,Rojo,2)]
-- xs′= [(Cuadrado,Azul,15),(Circulo,Rojo,1),(Triangulo,Azul,2)]


-- e)

-- xs= [(Circulo,Azul,5),(Cuadrado,Rojo,9),(Circulo,Azul,2)]
-- xs′= [(Circulo,Azul,1),(Circulo,Azul,18),(Triangulo,Azul,2)]


-- f)

-- xs= [(Triangulo,Rojo,5),(Cuadrado,Rojo,10),(Circulo,Rojo,2)]
-- xs′= [(Cuadrado,Azul,15),(Circulo,Rojo,1),(Triangulo,Azul,2)]


-- g)

-- xs= [(Triangulo,Rojo,5),(Cuadrado,Rojo,10),(Circulo,Rojo,2)]
-- xs′= [(Cuadrado,Azul,15),(Circulo,Amarillo,1),(Circulo,Verde,2)]


-- h)

-- xs= [(Triangulo,Rojo,5),(Cuadrado,Rojo,4),(Circulo,Rojo,2)]
-- xs′= [(Cuadrado,Azul,15),(Circulo,Rojo,1),(Triangulo,Azul,2)]


-- i)

-- xs= [(Circulo,Rojo,5),(Cuadrado,Rojo,10),(Circulo,Rojo,2)]
-- xs′= [(Cuadrado,Azul,15),(Circulo,Rojo,1),(Triangulo,Azul,2)]



-- 5)

-- a)

propA :: [Figura] -> Bool
propA [] = True
propA (x:xs) = rojo x && propA xs


-- b)

propB :: [Figura] -> Bool
propB [] = True
propB (x:xs) = tam x < 5 && propB xs


-- c)

propC :: [Figura] -> Bool
propC [] = True
propC (x:xs) | triangulo x && not (rojo x) = False
             | otherwise = propC xs


-- d)

propD :: [Figura] -> Bool
propD [] = False
propD (x:xs) = (cuadrado x && verde x) || propD xs


-- e)

propE :: [Figura] -> Bool
propE [] = True
propE (x:xs) | circulo x && not (azul x) || (tam x >= 10) = False
             | otherwise = propE xs


-- f)

propF :: [Figura] -> Bool
propF [] = True
propF (x:xs) | triangulo x && azul x = False
             | otherwise = propF xs


-- g)

propG :: [Figura] -> Bool
propG [] = True
propG (x:xs) | circulo x && amarillo x || verde x = False
             | otherwise = propG xs


-- h)

propH :: [Figura] -> Bool
propH [] = False
propH (x:xs) = (cuadrado x && tam x < 5) || propH xs


-- i)

existeCirculoRojo :: [Figura] -> Bool
existeCirculoRojo [] = False 
existeCirculoRojo (x:xs) = (circulo x && rojo x) || existeCirculoRojo xs

existeCuadradoRojo :: [Figura] -> Bool
existeCuadradoRojo [] = False 
existeCuadradoRojo (x:xs) = (cuadrado x && rojo x) || existeCuadradoRojo xs

propI :: [Figura] -> Bool
propI [] = True
propI (x:xs) = if existeCirculoRojo (x:xs) then existeCuadradoRojo (x:xs) else propI xs



-- 6)

-- xs = [(Cuadrado,Azul,11), (Circulo, Verde,5)]

-- a)

-- < ∃x : x ∈l xs : tam.x > 10 >


-- b)

-- < ∃x : x ∈l xs : cuadrado.x >


-- c)

-- < ∃x : x ∈l xs ∧ cuadrado.x : tam.x > 10 >


-- d)

-- < ∃x : x ∈l xs ∧ cuadrado.x ∧ azul.x : < ∃y : y ∈l ys ∧ circulo.y : tam.x > tam.y > >


-- e)

-- < ∃x : x ∈l xs ∧ circulo.x : ¬(azul.x) >



-- 7)

-- a)〈∀x : x ∈l xs ∧ (¬rojo.x ∨ triangulo.x) : tam.x > 10〉
-- b)〈∃x : x ∈l xs ∧ rojo.x : True〉∧〈∃y : y ∈ xs : ¬rojo.y〉
-- c)〈∀x : x ∈l xs ∧ rojo.x : cuadrado.x ∧ tam.x > 10〉

-- xs = [(Triangulo,Verde,16), (Cuadrado,Rojo,18)]



-- 8)

-- a)

-- 〈∀x : x ∈ Z : mod.x,2=0 ∨ mod.x,2/=0〉


-- b)

-- 〈∀x : x ∈l xs : x==1 ∨ x==0〉


-- c)

-- 〈∃x : x ∈l xs : x==1〉 => 〈∃y : y ∈l xs : y==0〉


-- g)

-- 〈∀i,j : 0 <= i < #xs ∧ 0 <= j < #xs-1 ∧ i /= j : xs!!i /= xs!!j 〉

-- En lenguaje natural: Para todo i, j en el rango definido de xs tal que i es diferente a j, se cumple que
-- el valor del indice en i es diferente al valor del indice en j.



-- 9)

-- a)

-- < ∃x,y : 0 <= x < length.xs ∧ 0 <= y < length.xs ∧ x /= y : xs!!x /= xs!!y >


-- b)

-- < ∃x : 0 <= x < length.xs ∧ xs!!x == 0 : < ∃y : 0 <= y < length.xs ∧ x /= y : xs!!y /= 0 > >


-- c)

-- < ∃i : 0 <= i < length.xs ∧ xs!!i == x : < ∃j : 0 <= j < length.xs ∧ i /= j : xs!!j /= x > >


-- d)

-- < ∃i : 0 <= i < length.xs ∧ xs!!i == cuadrado.x ∧ xs!!i == azul.x : < ∃j : 0 <= j < length.xs ∧ i /= j : ¬(xs!!j /= cuadrado.x ∧ xs!!j /= azul.x) > >



-- 10)

-- < ∃i,j : 0 <= i < j < length.xs : xs!!i == x ∧ xs!!j == x ∧ < ∃k : 0 <= k < length.xs ∧ k /= i ∧ k /= j : xs!!k /= x > >