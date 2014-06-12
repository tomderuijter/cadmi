
# Definitie image float, __new__ is nodig omdat floats immutable zijn.
# De image field bevat de image informatie, ander gedraagt het zich als een float.
# Note dat het resultaat van ieder operatie die je op een PerImageFloat uitvoert
# een normale float zal zijn. (Dus 1 + 1, in PerImageFloats, resulteerd in 2 als 
# een normale float)
class PerImageFloat(float):
    
    def __new__(self, value, image):
        return float.__new__(self, value)
        
    def __init__(self, value, image):
        self.image = image