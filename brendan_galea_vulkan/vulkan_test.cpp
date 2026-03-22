#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

int main() {
    // 1. Initialize Vulkan Instance
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Verification";
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkInstance instance;
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan instance! Check your drivers.\n";
        return -1;
    }

    // 2. Count and List Physical Devices (GPUs)
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        std::cerr << "Vulkan instance created, but no GPUs with Vulkan support found.\n";
    } else {
        std::cout << "Success! Found " << deviceCount << " Vulkan-capable device(s).\n";
        
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(device, &deviceProperties);
            std::cout << "Device Name: " << deviceProperties.deviceName << "\n";
        }
    }

    // 3. Cleanup
    vkDestroyInstance(instance, nullptr);
    return 0;
}
