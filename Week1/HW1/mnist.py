import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms

batch_size = 64
LR = 0.001
epochs = 10
DOWNLOAD_MNIST = True

# image transform
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5,), (0.5,))
])

# MNIST dataset
train_data = torchvision.datasets.MNIST(root='./mnist', train=True, transform=transform, download=DOWNLOAD_MNIST)
train_loader = torch.utils.data.DataLoader(dataset=train_data, batch_size=batch_size, shuffle=True, num_workers=2)

test_data = torchvision.datasets.MNIST(root='./mnist', train=False, transform=transform)
test_loader = torch.utils.data.DataLoader(dataset=test_data, batch_size=batch_size, shuffle=False, num_workers=2)

class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.conv1 = nn.Sequential(
            nn.Conv2d(in_channels = 1, out_channels = 16, kernel_size = 5, stride = 1, padding = 2,),# stride = 1, padding = (kernel_size-1)/2 = (5-1)/2
            nn.ReLU(),# (16, 28, 28)
            nn.MaxPool2d(kernel_size = 2),# (16, 14, 14)
        )
        self.conv2 = nn.Sequential(# (16, 14, 14)
            nn.Conv2d(16, 32, 5, 1, 2),# (32, 14, 14)
            nn.ReLU(),# (32,14,14)
            nn.MaxPool2d(2)# (32, 7, 7)
        )
        self.out = nn.Linear(32*7*7, 10)

    def forward(self, x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = x.view(x.size(0), -1)
        output = self.out(x)
        return output

cnn = CNN()
loss_func = nn.CrossEntropyLoss()
optimizer  = torch.optim.Adam(cnn.parameters(), lr = LR)

for epoch in range(epochs):
    cnn.train()
    running_loss = 0.0
    for i, (images, labels) in enumerate(train_loader):

        outputs = cnn(images)
        loss = loss_func(outputs, labels)
        
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        
        running_loss += loss.item()
        if (i + 1) % 100 == 0:  
            print(f'Epoch {epoch + 1}/{epochs}, Batch {i + 1}/{len(train_loader)}, Loss: {loss.item():.4f}')
    

    cnn.eval()
    correct = 0
    total = 0
    with torch.no_grad():
        for images, labels in test_loader:
            outputs = cnn(images)
            _, predicted = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
    
    test_acc = 100 * correct / total
    print(f'Epoch {epoch + 1}/{epochs}, Test Accuracy: {test_acc:.2f}%')
    
print('Training completed.')


