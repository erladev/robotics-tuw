from setuptools import find_packages
from setuptools import setup

setup(
    name='chatter_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('chatter_interfaces', 'chatter_interfaces.*')),
)
