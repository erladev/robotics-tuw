import yaml
import sys


class SafeLoaderIgnoreUnknown(yaml.SafeLoader):
    def ignore_unknown(self, node):
        return None 

SafeLoaderIgnoreUnknown.add_constructor(None, SafeLoaderIgnoreUnknown.ignore_unknown)


with open(sys.argv[1]) as f:
    f.readline()
    f.readline()
    data = yaml.safe_load(f)

K = data['K']['data']
D = data['D']['data']

fx, _, cx, _, fy, cy, _, _, _ = K
k1,k2,p1,p2,k3 = D

camera_config = {
    'fx': fx,
    'fy': fy,
    'cx': cx,
    'cy': cy,
    'k1': k1,
    'k2': k2,
    'k3': k3,
    'p1': p1,
    'p2': p2,

}

with open("stella_base_config.yaml", "r") as f:
    config = yaml.safe_load(f)
    config['Camera'].update(camera_config)

with open("stella_config_filled.yaml", "w") as f:
    yaml.dump(config, f)