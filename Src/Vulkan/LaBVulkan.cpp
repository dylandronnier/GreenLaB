#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define PARTICLE_COUNT 256 * 1024
#define DIM    512       // Square size of solver domain
#define DS    (DIM*DIM)  // Total domain size

class VulkanRendering : public VulkanExampleBase {
public:

  struct {
    VkPipelineVertexInputStateCreateInfo inputState;
    std::vector<VkVertexInputBindingDescription> bindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
  } vertices;
  
  // Resources for the graphics part of the example
  struct {
    VkDescriptorSetLayout descriptorSetLayout;	// Particle system rendering shader binding layout
    VkDescriptorSet descriptorSet;		// Particle system rendering shader bindings
    VkPipelineLayout pipelineLayout;		// Layout of the graphics pipeline
    VkPipeline pipeline;	  		// Particle rendering pipeline
  } graphics;
  
  // Resources for the compute part of the example
  struct {
    vks::Buffer storageBuffer;			// (Shader) storage buffer object containing the particles
    vks::Buffer uniformBuffer;		        // Uniform buffer object containing particle system parameters
    VkQueue queue;			        // Separate queue for compute commands (queue family may differ from the one used for graphics)
    VkCommandPool commandPool;			// Use a separate command pool (queue family may differ from the one used for graphics)
    VkCommandBuffer commandBuffer;		// Command buffer storing the dispatch commands and barriers
    VkFence fence;				// Synchronization fence to avoid rewriting compute CB if still in use
    VkDescriptorSetLayout descriptorSetLayout;	// Compute shader binding layout
    VkDescriptorSet descriptorSet;		// Compute shader bindings
    VkPipelineLayout pipelineLayout;		// Layout of the compute pipeline
    VkPipeline pipeline;			// Compute pipeline for updating particle positions
    struct computeUBO {				// Compute shader uniform block object
      float deltaT;				// Frame delta time
      int32_t particleCount = PARTICLE_COUNT;
    } ubo;
  } compute;
  
  // SSBO particle declaration
  struct Particle {
    glm::vec2 pos;								// Particle position
    glm::vec2 vel;								// Particle velocity
  };

  VulkanRendering() : VulkanExampleBase(ENABLE_VALIDATION)
  {
    title = "Compute shader particle system with LBM";
    settings.overlay = true;
  }

  ~VulkanRendering()
  {
    // Graphics
    vkDestroyPipeline(device, graphics.pipeline, nullptr);
    vkDestroyPipelineLayout(device, graphics.pipelineLayout, nullptr);
    vkDestroyDescriptorSetLayout(device, graphics.descriptorSetLayout, nullptr);
    
    // Compute
    compute.storageBuffer.destroy();
    compute.uniformBuffer.destroy();
    vkDestroyPipelineLayout(device, compute.pipelineLayout, nullptr);
    vkDestroyDescriptorSetLayout(device, compute.descriptorSetLayout, nullptr);
    vkDestroyPipeline(device, compute.pipeline, nullptr);
    vkDestroyFence(device, compute.fence, nullptr);
    vkDestroyCommandPool(device, compute.commandPool, nullptr);
    
    textures.particle.destroy();
    textures.gradient.destroy();
  }
  
};
  
int main(int argc, char* argv[]) {
    
    
  return 0;
}
