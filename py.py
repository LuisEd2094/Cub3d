import math

def calculate_player_angle(dirX, dirY):
    angle_rad = math.atan2(dirY, dirX)
    angle_deg = math.degrees(angle_rad)

    # Adjust the angle to be within [0, 360) degrees
    angle_deg = (angle_deg + 360) % 360

    return angle_rad

# Example usage:
dirX = 1  # Replace with the actual direction components
dirY = 0  # Replace with the actual direction components

player_angle = calculate_player_angle(dirX, dirY)
print(f"Player is looking at {player_angle} degrees.")