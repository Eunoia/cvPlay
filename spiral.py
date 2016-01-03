# pylint: disable=E1103
"""
Draws an Archimedean spiral on a set of tree rings.
"""
import cv2
import numpy as np

def cart2pol(i, j):
    """
    Converts cartesian coordinate to polar coordinates
    """
    rho = np.sqrt(i**2 + j**2)
    phi = np.arctan2(j, i)
    return(rho, phi)

def pol2cart(rho, phi):
    """
    Converts polar coordinates to Cartesian coordinate
    """
    x = rho * np.cos(phi)
    y = rho * np.sin(phi)
    return(x, y)

def main():
    """
    loads the image, runs the spiral, shows the results
    """
    image = cv2.imread('treering3.png', 0)
    height, width = image.shape
    center_x, center_y = height/2, width/2
    last_pair = (600, 600)

    for rho_phi in range(center_x):
        x, y = pol2cart(rho_phi, rho_phi%360)

        x = min(int(center_x+x), 1199)
        y = min(int(center_y+y), 1199)
        image[x, y] = 0
        cv2.line(image, last_pair, (x, y), 0, thickness=1, lineType=8)
        last_pair = (int(x), int(y))

    cv2.imshow('lines', image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

main()
