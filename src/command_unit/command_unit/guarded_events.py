class ControlEvent:
    def __init__(self):
        self.name = "SET NOT_ONLINE"
    
    def guard(self, control):
        return True
        
    def action(self):
        pass
    

class SetFlag(ControlEvent):
    pass

class Takeoff(ControlEvent):
    def guard(self, control):
        return not (control.not_online or control.emergency_set or not control.not_airborne)
    # action sends takeoff cmd to interface unit & clears na flag

class Emergency(ControlEvent):
    def guard(self, control):
        return not control.not_online
    
    # send control



class Control:
    def __init__(self, node):
        self.not_online=False # simulate
        self.not_airborne=True
        self.emergency_set=False
    
    def setNotOnline(self):
        self.not_online = True
