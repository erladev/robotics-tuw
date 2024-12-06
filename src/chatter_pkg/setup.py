from setuptools import find_packages, setup

package_name = 'chatter_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='root',
    maintainer_email='root@todo.todo',
    description='TODO: Package description',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'basic_node = chatter_pkg.tutorial_node:main',
            'publisher_node = chatter_pkg.publisher_node:main',
            'subscriber_node = chatter_pkg.subscriber_node:main'
        ],
    },
)
