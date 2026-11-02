import torch
from torch import nn

class MLP(nn.Module):
    def __init__(self):
        super().__init__()
        self.linear_relu = nn.Sequential(
                nn.Linear(1, 512),
                nn.ReLU(),
                nn.Linear(512, 512),
                nn.ReLU(),
                nn.Linear(512, 1),
            )
    def forward(self, x):
        return self.linear_relu(x)

def train(epochs, lr):
    mlp = MLP()

    x = torch.linspace(0, 2 * torch.pi, 1000).unsqueeze(1)
    y = torch.sin(x)

    loss_fn = nn.MSELoss()
    optimiser = torch.optim.SGD(mlp.parameters(), lr=lr)

    for e in range(epochs):
        pred_y = mlp(x)
        loss = loss_fn(pred_y, y)

        loss.backward()
        optimiser.step()
        optimiser.zero_grad()

        if e % 100 == 0:
            print(loss.item())
        

if __name__ == "__main__":
    train(1000, 0.01)
