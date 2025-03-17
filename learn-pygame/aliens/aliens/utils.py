from enum import IntEnum


class Direction(IntEnum):
    LEFT = -1
    STILL = 0
    RIGHT = 1

    @classmethod
    def change(cls, direction):
        if direction == cls.RIGHT:
            return cls.LEFT
        elif direction == cls.LEFT:
            return cls.RIGHT
        else:
            return cls.STILL

    @classmethod
    def from_value(cls, val):
        if val == -1:
            return cls.LEFT
        elif val == 0:
            return cls.STILL
        elif val == 1:
            return cls.RIGHT
        else:
            raise ValueError(f"Unknown integer value {val}!")
