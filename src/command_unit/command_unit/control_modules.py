class Module:
    def __init__(self, node, priority, static_status=""):
        self.node = node
        self.priority = priority
        self.active = False
        self.inhibited = False
        self.can_preempt = False
        self.static_status = static_status

    def should_activate(self):
        return False

    def get_status(self):
        return self.static_status

    def get_priority(self):
        return self.priority

class ExceptionStateModule(Module):
    # offline, not airborne, emergency set
    
    def __init__(self, node):
        super().__init__(self, node, 100, "offline")
        self.can_preempt = True

        self.last_status_at = None
        self.airborne = False
        self.emergency_set = False

        # set by callback to enable module 0=land 1=stop 2=emerg
        self.exception_command = None

    def should_activate(self):
        return self.last_status_at is None or not self.airborne \
                or self.emergency_set or self.exception_command is not None


class IdleModule(Module):
    def __init__(self, node):
        super().__init__(self, node, 2, "nav idle")


class NavModule(Module):
    def __init__(self, node):
        super().__init__(self, node, 3, "nav active")

    def should_activate(self):
        pass # return self.waypoint_queue or self.heading_queue

    def tick(self):
        # pop waypoint command
        # calculate direction & distance
        # dji.rotate()
        # dji.move()
        # else pop heading command
        pass


class ModuleOrchestrator:
    def __init__(self, node):
        self.modules = [ExceptionStateModule(node),
                        IdleModule(node),
                        NavModule(node)]
        self.modules.sort(Module.get_priority)
        self.active_module = None
