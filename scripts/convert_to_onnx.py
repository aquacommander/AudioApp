#!/usr/bin/env python3
"""
Convert Stable Audio model from PyTorch to ONNX format.

This script downloads the model from Hugging Face, converts it to ONNX,
and saves it for use with the C++ inference engine.
"""

import argparse
import os
import sys
from pathlib import Path
import torch
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


def convert_model_to_onnx(
    model_id: str = "stabilityai/stable-audio-open-small",
    output_path: str = "models/stable_audio.onnx",
    cache_dir: str = None
):
    """
    Convert Stable Audio model to ONNX format.
    
    Args:
        model_id: Hugging Face model identifier
        output_path: Path to save ONNX model
        cache_dir: Cache directory for downloads
    """
    try:
        logger.info(f"Loading model: {model_id}")
        
        # Try to load the model using different methods
        model = None
        processor = None
        
        # Method 1: Try stable-audio-tools
        try:
            from stable_audio_tools import get_pretrained_model
            logger.info("Attempting to load via stable-audio-tools...")
            pipeline = get_pretrained_model(model_id)
            if hasattr(pipeline, 'model'):
                model = pipeline.model
            else:
                model = pipeline
            logger.info("Loaded via stable-audio-tools")
        except ImportError:
            logger.info("stable-audio-tools not available")
        except Exception as e:
            logger.warning(f"stable-audio-tools failed: {e}")
        
        # Method 2: Try diffusers
        if model is None:
            try:
                from diffusers import DiffusionPipeline
                logger.info("Attempting to load via diffusers...")
                pipeline = DiffusionPipeline.from_pretrained(
                    model_id,
                    cache_dir=cache_dir,
                    torch_dtype=torch.float32
                )
                if hasattr(pipeline, 'unet'):
                    model = pipeline.unet  # Use the UNet part
                else:
                    model = pipeline
                logger.info("Loaded via diffusers")
            except Exception as e:
                logger.warning(f"diffusers failed: {e}")
        
        if model is None:
            raise RuntimeError("Could not load model using any method")
        
        model.eval()
        
        # Create output directory
        output_path = Path(output_path)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        
        # Prepare dummy inputs for tracing
        # Note: These shapes depend on the actual model architecture
        # You may need to adjust based on the Stable Audio model structure
        logger.info("Preparing model for ONNX export...")
        
        # Example input shapes (adjust based on actual model)
        batch_size = 1
        # These are placeholder shapes - need to match actual model inputs
        dummy_inputs = {
            'sample': torch.randn(batch_size, 8, 512),  # Example shape
            'timestep': torch.tensor([500]),
            'encoder_hidden_states': torch.randn(batch_size, 77, 768),
        }
        
        # Export to ONNX
        logger.info(f"Exporting to ONNX: {output_path}")
        
        # Try to export - this may need adjustment based on model structure
        try:
            torch.onnx.export(
                model,
                tuple(dummy_inputs.values()),
                str(output_path),
                input_names=list(dummy_inputs.keys()),
                output_names=['output'],
                dynamic_axes={
                    'sample': {0: 'batch_size'},
                    'encoder_hidden_states': {0: 'batch_size'},
                    'output': {0: 'batch_size'}
                },
                opset_version=17,
                do_constant_folding=True,
            )
            logger.info(f"✅ ONNX model saved to: {output_path}")
            
        except Exception as e:
            logger.error(f"ONNX export failed: {e}")
            logger.info("Note: Direct ONNX export may not work for all models.")
            logger.info("Consider using a model-specific conversion script or")
            logger.info("manually implementing the inference pipeline.")
            raise
        
        # Verify ONNX model
        try:
            import onnx
            onnx_model = onnx.load(str(output_path))
            onnx.checker.check_model(onnx_model)
            logger.info("✅ ONNX model verification passed")
        except ImportError:
            logger.warning("onnx package not available, skipping verification")
        except Exception as e:
            logger.warning(f"ONNX verification failed: {e}")
        
        return True
        
    except Exception as e:
        logger.error(f"Conversion failed: {e}")
        import traceback
        traceback.print_exc()
        return False


def main():
    parser = argparse.ArgumentParser(description="Convert Stable Audio model to ONNX")
    parser.add_argument(
        "--model-id",
        type=str,
        default="stabilityai/stable-audio-open-small",
        help="Hugging Face model ID"
    )
    parser.add_argument(
        "--output",
        type=str,
        default="models/stable_audio.onnx",
        help="Output ONNX model path"
    )
    parser.add_argument(
        "--cache-dir",
        type=str,
        default=None,
        help="Cache directory for downloads"
    )
    
    args = parser.parse_args()
    
    success = convert_model_to_onnx(
        model_id=args.model_id,
        output_path=args.output,
        cache_dir=args.cache_dir
    )
    
    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()

